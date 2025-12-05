Setup do docker em LabSetup normal como sempre

Fiz isso
> $ dockps // Alias for: docker ps --format "{{.ID}} {{.Names}}"
> $ docksh <id> // Alias for: docker exec -it <id> /bin/bash
> // The following example shows how to get a shell inside hostC
> $ dockps
> b1004832e275 hostA-10.9.0.5
> 0af4ea7a3e2e hostB-10.9.0.6
> 9652715c8e0a hostC-10.9.0.7
> $ docksh 96
> root@9652715c8e0a:/#
> // Note: If a docker command requires a container ID, you do not need to
> // type the entire ID string. Typing the first few characters will
> // be sufficient, as long as they are unique among all the containers.

Só q o meu foi assim
``` txt
[12/04/25]seed@VM:~/.../Labsetup$ dockps
781bfbeb90b8  www-10.9.0.80
[12/04/25]seed@VM:~/.../Labsetup$ ^C
[12/04/25]seed@VM:~/.../Labsetup$ docksh 781bfbeb90b8
bash: $'\r': command not found
```
---




"[12/04/25]seed@VM:~/.../Labsetup$ dockps
781bfbeb90b8  www-10.9.0.80
"
"
[12/04/25]seed@VM:~/.../Labsetup$ docksh 781bfbeb90b8
bash: $'\r': command not found
bash: $'\r': command not found
bash: $'\r': command not found
bash: $'\r': command not found
bash: $'\r': command not found
cd home1bfbeb90b8:/app# 
"

Key-> "1001:123456

1002:983abe

1003:793zye

1004:88zjxc

1005:xciujk"

Vou usar o "1001:123456
uid : chave"


"[12/04/25]seed@VM:~/.../Labsetup$ echo -n "123456:myname=Divaldo&uid=1001&lstcmd=1" | sha256sum
7bada21123c984d2f2c90b218bc828b4b3ae343d900899870298a2f4554a8bc4  -
"


"http://10.9.0.80/?myname=Divaldo&uid=1001&lstcmd=1&mac=7bada21123c984d2f2c90b218bc828b4b3ae343d900899870298a2f4554a8bc4"
COnsegui ver a interface e agora vou tentar baixar.



Agora vou cirar o hask para download
"
[12/04/25]seed@VM:~/.../Labsetup$ echo -n "123456:myname=Divaldo&uid=1001&lstcmd=1&download=secret.txt" | sha256sum
85277beea9c6451294b1da9c983b048b8e7c9e7a047008b99a7ae26abebf2c7d  -
[12/04/25]seed@VM:~/.../Labsetup$ 
"

E fui para "http://10.9.0.80/?myname=Divaldo&uid=1001&lstcmd=1&download=secret.txt&mac=85277beea9c6451294b1da9c983b048b8e7c9e7a047008b99a7ae26abebf2c7d"
E funcionou
<img width="1031" height="462" alt="{D34C9A74-C18D-433E-801E-ADE3C871A9F5}" src="https://github.com/user-attachments/assets/1fa1e8c6-0655-451b-9763-682a2a1e4154" />

Consegui enviar um pedido válido contendo os comandos lstcmd e download. O servidor validou o MAC e retornou o conteúdo do arquivo secret.txt, conforme mostra a imagem.

---
"Internal Server Error

The server encountered an internal error and was unable to complete your request. Either the server is overloaded or there is an error in the application."

O "Internal Server Error" (Erro 500) é muito importante aqui. Ele significa que o seu MAC está correto (se estivesse errado, o erro seria "Access Denied" ou "Invalid MAC"), mas o programa do servidor quebrou ao tentar ler o arquivo.
---

# Task 2


O "Guião" diz: "calcular o padding da mensagem no formato: <key>:myname=<name>&uid=<uid>&lstcmd=1".

A string é: 123456:myname=Divaldo&uid=1001&lstcmd=1

``` txt
Vamos contar os caracteres (bytes):

    123456 = 6

    : = 1

    myname=Divaldo = 14

    &uid=1001 = 9

    &lstcmd=1 = 9

    Total = 39 bytes
```

O bloco do SHA-256 tem 64 bytes. O padding é preenchido assim:

    A mensagem original (39 bytes).

    Um byte 0x80 (início do padding).

    Vários bytes 0x00 (zeros).

    Os últimos 8 bytes são o tamanho da mensagem original em bits (Big Endian).

Cálculos:

    Tamanho da mensagem (M) = 39 bytes.

    Tamanho em bits = 39 * 8 = 312 bits (Em hexadecimal: 0x0138).

    Tamanho do Padding = 64 - 39 = 25 bytes.


Estrutura do Padding (25 bytes):

    1 byte: \x80

    16 bytes: \x00 (Zeros para encher o buraco)

    8 bytes (Tamanho em bits): \x00\x00\x00\x00\x00\x00\x01\x38

O Padding em Hexadecimal:
\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x38

    Importante para a URL: Você terá de converter isso para URL Encoding (trocar \x por %).
    Padding URL Encoded:
    %80%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%00%01%38

Guarde este valor URL Encoded, vamos usá-lo na URL final.

---


