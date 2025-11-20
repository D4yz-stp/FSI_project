
Firstly we went to the `Labsetup` directory, and used these 2 commands in the terminal to set up the lab environment

- `$ docker-compose build`
- `$ docker-compose up`

---

# Task 1

A letter is always replaced by the same letter during the encryption described in the Task 1. So our job is to find out the original text using frequency analysis

## Step 1 

We started by generating the encryption key basically the substitution table. To do that, we took the alphabet from a to z and shuffled it in Python. The permuted alphabet became our key for the cipher. We used the following program to create it

So we created a file named `Key_subs_table.py`
``` Python
#!/bin/env python3

import random



s = "abcdefghijklmnopqrstuvwxyz"

list = random.sample(s, len(s))

key = ’’.join(list)

print(key)
```
We could observe that "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" // eliminar

## Step 2

I created the file "article.txt" and used the folowwing commands, to generaty the "lowercase.txt" and "plaintext.txt"
In the "article.txt" We did keep the spaces between words, because the guide intructed us to do it
- `tr [:upper:] [:lower:] < article.txt > lowercase.txt`
- `tr -cd ’[a-z][\n][:space:]’ < lowercase.txt > plaintext.txt`

We converted all upper cases to lower cases to the "lowercase.txt" file, and then removed all the punctuations and number to the ""plaintext.txt".

The "article.txt" is 
``` text
THIS IS A SAMPLE ARTICLE 123!
It Has UPPERCASE, lowercase, numbers 987, and punctuation!!!
Monoalphabetic ciphers are simple, but historically important.
```
(example text)
The "lowercase.txt" ended up to be
``` text
this is a sample article 123!
it has uppercase, lowercase, numbers 987, and punctuation!!!
monoalphabetic ciphers are simple, but historically important.
```
(example text)
And finally the plaintext.txt ended up to be 
``` text
this is a sample article 
it has uppercase lowercase numbers  and punctuation
monoalphabetic ciphers are simple but historically important
``` 
(example text)
## Step 3

Next, we used the tr command to perform the encryption. Our substitution table only applies to letters, so we encrypted the alphabetic characters while keeping spaces and newline characters unchanged.

So the "plaintext.txt" were converted to the file "ciphertext.txt"


Now we need to figure it out the original text from "ciphertext.txt"
We converted the "ytn" to "THE" with the command 
- `tr “ytn” “THE” < ciphertext.txt > test.txt`

The word "THvT" were observed alot of times, so to us that means that it was equal to "THAT"

so we did 
- `tr “v” “A” < test.txt > test1.txt`


"tr 'ytnhvfxqgioulpacmzred' 'THERAVOSBLFNWDCMIUGPY' < ciphertext.txt"
