#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 

#define BLOCK_SIZE 1
int main(int argc, char *argv[]) {
    // prog defence
    assert(argc == 3);


    FILE* fin = fopen(argv[1], "rb");
    FILE* fout = fopen(argv[2], "wb");
    char buf[BLOCK_SIZE];

    while (1) {
        size_t nb_read = fread(buf, 1, BLOCK_SIZE, fin);
        if (nb_read == 0) break;
        fwrite(buf, 1, nb_read, fout);
    }

    fclose(fin);
    fclose(fout);

}
