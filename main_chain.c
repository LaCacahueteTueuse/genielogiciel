
#include "matrix.h"
#include "mult.h"
#include "chain.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    matrix *mat, c;
    int nb_matrices, i;

    scanf("%d", &nb_matrices);
    mat = malloc(nb_matrices*sizeof(matrix));

    for(i = 0; i < nb_matrices; i++)
        mat[i] = matrix_read();

    c = chain_product(nb_matrices, mat);
    matrix_print(stdout, c);
    
    // mat[i] is freed in chain_product
    free(mat);
    matrix_free(c);
    return 0;
}

