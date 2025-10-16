#include <stdio.h>
#include <unistd.h>
int main() {
    printf("Muh ha ha ha ha!!\n");
    if (geteuid() == 0) printf("I have root privilege!\n");
    return 0;
}
