# SEED Labs – Buffer Overflow Attack Lab (Set-UID Version)

I started by using these codes:
1. `$ sudo sysctl -w kernel.randomize_va_space=0`
2. `$ sudo ln -sf /bin/zsh /bin/sh`

Where the 1. is to temporarily turn off ASLR so stack addresses stay the same between runs, making debugging and offset hunting reliable.
And the 2. points `/bin/sh` to zsh so any spawned shell is interactive and easier to use.
Together they make exploit testing more reproducible basically

## 5

I am in the directory "category-software/Buffer_Overflow_Setuid" of the seed labs

### 5.1

The objective of this exercise is to determine the exact number of bytes from the start of the buffer to the saved return address on the stack, the lab itself instructs compiling the program with debug symbols, running it under a debugger, overflowing it with a test pattern, and inspecting the stack to identify that precise offset.

It was intructed to me to use `-g` flag to my commands, so in that way i have the debugging information is added to the binary

I used `make` to generate all debug binaries

Afterwards, i used all these commands line by line 
<img width="658" height="244" alt="{BCC929BB-7C9B-4FF4-B715-E1432A44B049}" src="https://github.com/user-attachments/assets/32754c40-f4cd-4984-ba64-02a4c22e3cc7" />
<img width="583" height="116" alt="{41BF9382-3DA2-4CE5-9F74-D1EAFAC86DF0}" src="https://github.com/user-attachments/assets/2a703d1b-ad38-4e68-81c8-37fc64012835" />

The team created an empty badfile to hold the payload, launched the debug build under GDB (gdb ./stack-L1-dbg), set a breakpoint at the vulnerable function (b bof) and ran the program (run) until the breakpoint, stepped (next) until the function prologue completed, inspected the frame pointer (p $ebp) and buffer address (p &buffer) to compute the saved return-address offset, and then exited GDB (quit).

We have only a few differences, for example, when i used `b bof` in the gdb-peda terminal i got "Breakpoint 1 at 0x80485a1: file stack.c, line 20." instead of "Breakpoint 1 at 0x124d: file stack.c, line 18."

### 5.2

The objective is to complete the provided `exploit.py` skeleton to generate a badfile containing a NOP sled, shellcode, and the correct return‑address/offsets so the buffer‑overflow can be exploited.

So, we needed to change the shellcode to an x86 execve("/bin/sh") payload, set start to the index where the shellcode sits in the payload, set ret to an address inside the buffer (preferably the NOP‑sled), and set offset to the byte position in the file where the saved return‑address is overwritten in `exploit.py`.

So i entered in the binary debugger with `b bof`, and did these things in order
- run
- next
- next
- p &buffer

So i could get the buffer address that is "0xbfffe65c", we will use this later.

I used a standard 32‑bit execve('/bin/sh') shellcode because it’s compact and avoids null bytes (so strcpy won’t truncate it). The shellcode pushes '/bin//sh' onto the stack, sets ebx to point to the string and ecx/edx to NULL, then issues execve via int 0x80. It is placed inside the payload after a NOP sled so the return address can land anywhere in the sled and still reach the shellcode
```c
shellcode = (
    b"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e"
    b"\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"
)
```

I set the start to 32 because I wanted a generous NOP area before the shellcode. The start indicates the byte position in the payload where the shellcode begins. Reserving about 32 bytes of 0x90 provides slack in case the jump lands slightly before the payload.

The ret should point into the NOP sled, ideally a few bytes before or at the start of the shellcode. I calculated it as the buffer base plus 32. For example, if the buffer begins at 0xbfffe65c, then ret = 0xbfffe65c + 32 = 0xbfffe67c.

Finally, I set the offset to 104 because the saved return address lies immediately after the 100‑byte buffer and the 4‑byte saved EBP. Therefore, overwriting the return address requires writing at byte position 100 + 4 = 104 in the payload.

Then used the command `python3 exploit.py` to generate the contents for badfile.

And tried `./stack-L1` to launch the attack, but we got an error "Input size: 517 Segmentation fault"

Decided to not give up, i did a diagnoses, and did these commans on the dbb terminal to see what is going on

1. b bof
2. run < badfile
3. next
4. next
5. p/x &buffer
6. p/x $ebp
7. x/40bx $ebp-120
8. x/8bx $ebp+4
9. info registers
10. x/i 0xbfffe67c

After getting the analysis of some IA, i could see that "0xbfffe6cc - 0xbfffe65c = 0x70 = 112" So the offset i was using was wrong, its not 104, it should be 112, but...
It did not work also, so i changed the start to 40, 60 but i would still not work and give the same error message

Frustated with this, i was doing trying to see some debugging on videos and chatghpt for more time, but at the end nothing worked
