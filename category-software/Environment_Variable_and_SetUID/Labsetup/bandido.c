#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    if (remove(filename) == 0) {
        printf("O ficheiro '%s' foi deletado com sucesso.\n", filename);
    } else {
        perror("Erro ao deletar o ficheiro");
        return 1; 
    }
    return 0; 
}