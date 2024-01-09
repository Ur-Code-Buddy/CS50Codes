#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Improper usage.");
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename,"r");

    if (file == NULL ){
        printf("No such file found.\n");
        return 1;
    }

    uint8_t buffer[4];
    fread(buffer, 1, 4, file);

    for (int i = 0; i < 4; i++){
        printf("%i",buffer[i]);
    }
    fclose(file);
    printf("\n");

}
