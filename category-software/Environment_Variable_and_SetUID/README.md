# Guide

Comecei por criar uma pasta partilhada no SeedLabs, coloquei no directorio /media.

De seguida eu escrevi "printenv PWD" para poder ver as variaveis globais, mas quando fiz o mesmo codigo na pasta /media/Environment_Variable_and_SetUID/Labsetup não deu o mesmo resultado.

## 2.2
O objetivo da task é verificar se as variáveis de ambiente do processo pai são herdadas pelo processo filho após a chamada de fork().

Decidi então seguir os passos do guião

Compilei o myprintenv.c com "gcc myprintenv.c" que deu um a.out, que logo a seguir fiz "a.out > file" para poder ver as variaveis globais, consegui então o retorno que havia tido quando fiz printenv PWD no directorio inicial.

Agora vou colocar o printenv() do processo filho do myprintenv.c em comentario, e descomentar o printenv.c do processo pai.
Pude reparar que os 2 retornaram literalmente a mesma coisa quanto às variáveis de ambiente!

<img width="343" height="302" alt="{AFA5A446-B36F-47F0-95D9-2D8EF8851F49}" src="https://github.com/user-attachments/assets/7a9271e4-7dcf-4141-8f50-84ca74816c16" />

"XDG_VTNR=7
XDG_SESSION_ID=c1
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/seed
CLUTTER_IM_MODULE=xim
SESSION=ubuntu
ANDROID_HOME=/home/seed/android/android-sdk-linux
GPG_AGENT_INFO=/home/seed/.gnupg/S.gpg-agent:0:1
TERM=xterm-256color
VTE_VERSION=4205
XDG_MENU_PREFIX=gnome-
SHELL=/bin/bash
DERBY_HOME=/usr/lib/jvm/java-8-oracle/db
QT_LINUX_ACCESSIBILITY_ALWAYS_ON=1
LD_PRELOAD=/home/seed/lib/boost/libboost_program_options.so.1.64.0:/home/seed/lib/boost/libboost_filesystem.so.1.64.0:/home/seed/lib/boost/libboost_system.so.1.64.0
WINDOWID=60817418
UPSTART_SESSION=unix:abstract=/com/ubuntu/upstart-session/1000/1442
GNOME_KEYRING_CONTROL=
GTK_MODULES=gail:atk-bridge:unity-gtk-module
USER=seed
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
QT_ACCESSIBILITY=1
LD_LIBRARY_PATH=/home/seed/source/boost_1_64_0/stage/lib:/home/seed/source/boost_1_64_0/stage/lib:
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
SSH_AUTH_SOCK=/run/user/1000/keyring/ssh
DEFAULTS_PATH=/usr/share/gconf/ubuntu.default.path
XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/usr/share/upstart/xdg:/etc/xdg
DESKTOP_SESSION=ubuntu
PATH=/home/seed/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:.:/snap/bin:/usr/lib/jvm/java-8-oracle/bin:/usr/lib/jvm/java-8-oracle/db/bin:/usr/lib/jvm/java-8-oracle/jre/bin:/home/seed/android/android-sdk-linux/tools:/home/seed/android/android-sdk-linux/platform-tools:/home/seed/android/android-ndk/android-ndk-r8d:/home/seed/.local/bin
QT_IM_MODULE=ibus
QT_QPA_PLATFORMTHEME=appmenu-qt5
XDG_SESSION_TYPE=x11
PWD=/media/sf_Environment_Variable_and_SetUID/labsetup
JOB=unity-settings-daemon
XMODIFIERS=@im=ibus
JAVA_HOME=/usr/lib/jvm/java-8-oracle
GNOME_KEYRING_PID=
LANG=en_US.UTF-8
GDM_LANG=en_US
MANDATORY_PATH=/usr/share/gconf/ubuntu.mandatory.path
COMPIZ_CONFIG_PROFILE=ubuntu-lowgfx
IM_CONFIG_PHASE=1
GDMSESSION=ubuntu
SESSIONTYPE=gnome-session
GTK2_MODULES=overlay-scrollbar
SHLVL=1
HOME=/home/seed
XDG_SEAT=seat0
LANGUAGE=en_US
LIBGL_ALWAYS_SOFTWARE=1
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
UPSTART_INSTANCE=
UPSTART_EVENTS=xsession started
XDG_SESSION_DESKTOP=ubuntu
LOGNAME=seed
COMPIZ_BIN_PATH=/usr/bin/
DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-fz0sx2JiI3
J2SDKDIR=/usr/lib/jvm/java-8-oracle
XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop
QT4_IM_MODULE=xim
LESSOPEN=| /usr/bin/lesspipe %s
INSTANCE=
UPSTART_JOB=unity7
XDG_RUNTIME_DIR=/run/user/1000
DISPLAY=:0
XDG_CURRENT_DESKTOP=Unity
GTK_IM_MODULE=ibus
J2REDIR=/usr/lib/jvm/java-8-oracle/jre
LESSCLOSE=/usr/bin/lesspipe %s %s
XAUTHORITY=/home/seed/.Xauthority
_=./a.out
OLDPWD=/media/sf_Environment_Variable_and_SetUID
"

--- 
## 2.3

### step 1
O objetivo dessa tarefa é analisar o que acontece com as variáveis de ambiente quando um novo programa é executado com execve(), queremos saber se elas são herdadas pelo programa carregado.

Seguindo os passos, executei o ficheiro myenv.c com "gcc myenv.c" que retornou um a.out, que logo em seguida fiz "a.out > file"

<img width="386" height="346" alt="{45D21D20-71C8-46C8-9E9A-3D79B9250C34}" src="https://github.com/user-attachments/assets/131ac1bb-5f92-4a8c-9c40-c5d6cf38f567" />

Obtive um ficheiro vazio

### step 2

Mudei a linha "execve("/usr/bin/env", argv, NULL);  " para "execve("/usr/bin/env", argv, environ);" E executei os mesmos comandos de antes

### step 3

Notei que obtive literalmente as mesmas variaveis globais do processo pai( n houve uma criaçao de processo filho, pai é usado apenas como referencia) 

Portanto concluimos que o execve() substitui o programa atual sem criar um novo processo e apenas transmite as variáveis de ambiente se estas forem explicitamente passadas como argumento. Caso contrário, o novo programa é executado com um ambiente vazio.

---
## 2.4

O objetivo desta tarefa é analisar o que acontece com as variáveis de ambiente quando um novo processo é executado através da função `system()`. Diferente da execve(), que não cria um processo filho mas apenas muda o processo atual. A função system() executa o comando por meio de um novo terminal `(/bin/sh -c command)`, criando assim um novo processo filho. Queremos verificar se as variáveis de ambiente do processo original são herdadas por esse novo processo.

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
system("/usr/bin/env");
return 0 ;
}
```

Ao executar o comando com `gc myenv.c -o myenvsys` e `./myenvsys > file`, pude constatar que a função `system()` não troca o programa que está rodando; em vez disso, ela cria um processo filho para correr um novo terminal `(/bin/sh)`. Como `system()` usa internamente `execl()`, que por sua vez chama `execve()` com o mesmo conjunto de variáveis do processo pai, o processo filho acaba por herdar automaticamente todas as variáveis de ambiente.

---
## 2.5 

O objetivo desta tarefa é analisar como as variáveis de ambiente são tratadas quando um programa Set-UID é executado. Especificamente, queremos ver se as variáveis de ambiente do usuário que executa o programa são herdadas pelo processo do Set-UID, considerando que ele assume privilégios do proprietário (ex: root).

### step 1

```c
#include <stdio.h>
#include <stdlib.h>
extern char **environ;
int main()
{
int i = 0;
while (environ[i] != NULL) {
printf("%s\n", environ[i]);
i++;
}
}
```

### step 2

Agora, compilei o codigo com `gcc foo.c -o foo`, e usei esses comandos logo em seguida `sudo chown root foo` ( mudei o proprietário para root ), e `sudo chmod 4755 foo` ( tornei o programa Set-UID )

Tudo isso feito no root terminal que acessei depois de usar  `sudo -i`

### step 3

Agora tive de executar esses comandos no terminal

1. `export PATH=/home/seed/bin:$PATH` ( definir o path ) 
2. `export LD_LIBRARY_PATH=/home/seed/lib` ( definir o lb library path ) 
3. `export MY_VAR="banaNa"` 

Verifiquei o file depois do comando `./foo > file` e para a minha surpresa, foi possível ver que todas as variáveis definidas pelo usuário aparecem com os valores atualizados no file. No meu teste vi todas as variáveis que defini (`MY_VAR`, `LD_LIBRARY_PATH`, `PATH`) aparecerem no programa Set‑UID, mas senti dúvidas quanto a esse exercício. Depois de pesquisar, descobri que isso não é sempre o comportamento padrão, em muitas distribuições/configurações variáveis potencialmente perigosas são filtradas por razões de segurança. Assim, embora eu tenha visto todas as minhas variáveis nesse ambiente, o resultado pode variar conforme a versão da libc, flags do kernel (securebits), políticas do sudo, ou como o binário foi invocado.

---
## 2.6

O objetivo desta tarefa é testar se um programa Set‑UID que usa system("ls") pode ser forçado a executar um ficheiro malicioso controlado pelo utilizador (colocado no início do PATH como variavel do ambiente) e verificar se esse ficheiro corre com privilégios do dono (root).

```c
int main()
{
system("ls");
return 0;
}
```
Este é o "seis.c" que vou usar para ser a vítima, 
e este
```c
int main() {
    printf("Muh ha ha ha ha!!\n");
    if (geteuid() == 0) printf("I have root privilege!\n");
    return 0;
}
```
É o "bad_code.c" que vai ser o ficheiro malicioso, 
Começei então por compilar o seis.c e logo em seguida o transformei em um ficheiro root e Set-UID

Compilei o "bad_code.c" assim -> "gcc -o ls bad_code.c" e em seguida defini/alterei variáveis do ambiente com `export PATH=/home/seed:$PATH` 
E com isso quando executei o seis, com `./seis` Ele retornou ->
```c
[10/13/25]seed@VM:~/Documents$ ./seis
Muh ha ha ha ha!!
```
Então, sim eu consegui executar o codigo malicioso.
No entanto, embora o binário malicioso ( bad_code.c -> ls ) tenha sido executado (vejo o output "Muh ha ha ha ha!!"), não apareceu a mensagem "I have root privilege!". Isto indica que, no meu ambiente, o processo malicioso não correu com EUID = 0.
Decidi adentrar na internet e buscar entender porquê, e vi essa explicação que faz sentido 

>Likely reasons:
>
>The shell called by system() (e.g., /bin/sh — often dash) may drop the EUID as a mitigation;
>
>The target program might have already reduced its privileges before calling system(), so the child inherits limited rights;
>
>Some filesystems (e.g., vboxsf) do not respect the set‑uid bit, so the user’s executable doesn’t gain the owner’s privileges.
>
>In other words: the PATH trick worked to run the user’s binary, but these limitations prevented privilege escalation in this test."

---

## 2.8

### step 1

O objetivo desta tarefa é compreender os problemas que o `system()` tem quanto à criação de terminais/shell para executar programas, mas o foco principal é explorar a vulnerabilidade de um programa *Set-UID* em ficheiros que são non-writable

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char *v[3];
  char *command;

  if(argc < 2) {
    printf("Please type a file name.\n");
    return 1;
  }

  v[0] = "/bin/cat"; v[1] = argv[1]; v[2] = NULL;
  // /bin/cat/ls
  command = malloc(strlen(v[0]) + strlen(v[1]) + 2);
  sprintf(command, "%s %s", v[0], v[1]);

  // Use only one of the followings.
  system(command);
  // execve(v[0], v, NULL);

  return 0 ;
}
```

Compilei este ficheiro com `gcc catall.c -o catall`, ele tem 2 alternativas para executar um novo programa, com `system` ou `execve`, mas como foi-me pedido para apenas fazer o step 1, eu vou explorar a vulnerabilidade do `system()`, pois também diferente do execve, o `system` executa o comando em uma shell

---

## 2.9 

O objetivo desta tarefa é testar a vulnerabilidade de *capability leaking*, que é quando um programa Set-UID drop ao UID, só que nós temos de investigar de ele ainda assim deixa previlégios que podem ser usados como vulnerabilidade.

Temos esse codigo que é um programa Set-UID mas que perdi o seu UID com `setuid(getuid());`
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void main()
{
  int fd;
  char *v[2];

  /* Assume that /etc/zzz is an important system file,
   * and it is owned by root with permission 0644.
   * Before running this program, you should create
   * the file /etc/zzz first. */
  fd = open("/etc/zzz", O_RDWR | O_APPEND);        
  if (fd == -1) {
     printf("Cannot open /etc/zzz\n");
     exit(0);
  }

  // Print out the file descriptor value
  printf("fd is %d\n", fd);

  // Permanently disable the privilege by making the
  // effective uid the same as the real uid
  setuid(getuid());                                

  // Execute /bin/sh
  v[0] = "/bin/sh"; v[1] = 0;
  execve(v[0], v, 0);                             
}
```

Começei compilando esse codigo `gcc cap_leak.c -o cap_leak`, logo em seguida fi-lo propriedade do root e a transformei em um Set-UID com esses comandos

1. `sudo chown root cap_leak`
2. `sudo chmod4755 cap_leak`

Agora, como é dito no codigo, não existe um ficheiro importante chamado "zzz" no caminho /etc, então vou ter de criar um ficheiro de texto "zzz" para servir só de teste.

>* Before running this program, you should create
>   * the file /etc/zzz first. */

Criei esse file com `sudo touch /etc/zzz`, mas agora tenho de faze-lo ser propriedade do root e dar-lhe uma permissão específica

>/* Assume that /etc/zzz is an important system file,
>   * and it is owned by root with permission 0644.

E com isso eu já estava pronto para executar o cap_leak, e assim fiz com o comando `./cap_leak`

E obtive isto

```c
[10/13/25]seed@VM:~/Documents$ ./cap_leak
fd is 3
$
```
Não foi só isso, porque é na verdade um terminal de um novo programa,
Tentei `rm -f /etc/zzz`, mas deu 
```c
$ rm -f /etc/zzz
rm: cannot remove '/etc/zzz': Permission denied
```

Decidi então usar o fd para certificar que não temos mais vulnerabilidades, usei o comando `cat 'linha maliciosa' > &3`, e para a minha surpresa funcionou 
```c
$ sudo cat /etc/zzz
linha maliciosa
linha maliciosa
$ 
```
Ou seja, apesar de eu não ter autorização de root em vários comando, eu consigo adicionar informações no ficheiro /etc/zzz que é do root com uma permissão específica só porque eu tinha o endereço do fd, então é seguro afirmar que o novo programa herdou o esse descritor do programa inicial.

Em suma, o teste demonstrou a vulnerabilidade de *capability leaking*, eu vi que, embora o processo tenha revogado o root com setuid(getuid()), ele deixou para trás o descritor de ficheiro (FD) aberto para o /etc/zzz. O shell que o programa executou simplesmente herdou esse FD "vazado", e foi assim que consegui escrever no ficheiro protegido. Ou seja, setuid() sozinho não basta; é preciso limpar todos os recursos privilegiados (fechar os FDs) para garantir a segurança.
