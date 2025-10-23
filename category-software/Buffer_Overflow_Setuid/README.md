# SEED Labs – Buffer Overflow Attack Lab (Set-UID Version)

I started by using these codes:
1. `$ sudo sysctl -w kernel.randomize_va_space=0`
2. `$ sudo ln -sf /bin/zsh /bin/sh`

Where the 1. is to <....>
And the 2. to <...>
So pretty much the will allow me to <...>



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


