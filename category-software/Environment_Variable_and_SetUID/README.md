# Guide

Comecei por criar uma pasta partilhada no SeedLabs, coloquei no directorio /media.

De seguida eu escrevi "printenv PWD" para poder ver as variaveis globais, mas quando fiz o mesmo codigo na pasta /media/Environment_Variable_and_SetUID/Labsetup não deu o mesmo resultado.

### 2.2
O objetivo da task é verificar se as variáveis de ambiente do processo pai são herdadas pelo processo filho após a chamada de fork().

Decidi então seguir os passos do guião

Compilei o myprintenv.c com "gcc myprintenv.c" que deu um a.out, que logo a seguir fiz "a.out > file" para poder ver as variaveis globais, consegui então o retorno que havia tido quando fiz printenv PWD no directorio inicial.

Agora vou colocar o printenv() do processo filho do myprintenv.c em comentario, e descomentar o printenv.c do processo pai.
Pude reparar que os 2 retornaram literalmente a mesma coisa quanto as variaveis ambientais!

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
### 2.3

step 1
O objetivo dessa tarefa é analisar o que acontece com as variáveis de ambiente quando um novo programa é executado com execve(), queremos saber se elas são herdadas pelo programa carregado.

Seguindo os passos, executei o ficheiro myenv.c com "gcc myenv.c" que retornou um a.out, que logo em seguida fiz "a.out > file"

<img width="386" height="346" alt="{45D21D20-71C8-46C8-9E9A-3D79B9250C34}" src="https://github.com/user-attachments/assets/131ac1bb-5f92-4a8c-9c40-c5d6cf38f567" />

Obtive um ficheiro vazio

step 2

Mudei a linha "execve("/usr/bin/env", argv, NULL);  " para "execve("/usr/bin/env", argv, environ);" E executei os mesmos comandos de antes

step 3

Notei que obtive literalmente as mesmas variaveis globais do processo pai( n houve uma criaçao de processo filho, pai é usado apenas como referencia) 

Portanto concluimos que o execve() substitui o programa atual sem criar um novo processo e apenas transmite as variáveis de ambiente se estas forem explicitamente passadas como argumento. Caso contrário, o novo programa é executado com um ambiente vazio.

---
### 2.4

O objetivo desta tarefa é analisar o que acontece com as variáveis de ambiente quando um novo processo é executado através da função `system()`,  diferente da `execve()`, que não cria um processo filho, mas apenas muda a função o processo atual. A função system() executa o comando por meio de um novo terminal `(/bin/sh -c command)`, criando assim um novo processo filho. Queremos verificar se as variáveis de ambiente do processo original são herdadas por esse novo processo.

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
system("/usr/bin/env");
return 0 ;
}
```

Ao executar o comando com `gc myenv.c -o myenvsys` e `./myenvsys > file`, pude constar que a função `system()` não troca o programa que está rodando; em vez disso, ela cria um processo filho para rodar um novo terminal `(/bin/sh)`. Como `system()` usa internamente `execl()`, que por sua vez chama `execve()` com o mesmo conjunto de variáveis do processo pai, o processo filho acaba herdando automaticamente todas as variáveis de ambiente.

