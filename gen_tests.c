
#include "matrix.h"
#include "mult.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int random_int(int min, int max)
{
    return min + (rand() % (max - min));
}

int main(int argc, char *argv[])
{
    int nb_matrices, i, current_size, min_dim, max_dim;
    matrix current_product;

    scanf("%d", &nb_matrices);

    srand(time(NULL));
    char fname[100];
    int identifier = random_int(0, 1000);
    sprintf(fname, "chain_tests/inp-%.4d-%d", nb_matrices, identifier);    
    FILE* in_stream = fopen(fname, "w");
    sprintf(fname, "chain_tests/out-%.4d-%d", nb_matrices, identifier);
    FILE* out_stream = fopen(fname, "w");
    // TODO check for errors

    fprintf(in_stream, "%d\n", nb_matrices);

    scanf("%d", &min_dim);
    scanf("%d", &max_dim);
    current_size = random_int(min_dim, max_dim); 
    for(i = 0; i < nb_matrices; i++)
    {
        int new_size, j, k;
        matrix a;

        scanf("%d", &min_dim);
        scanf("%d", &max_dim);
        new_size = random_int(min_dim, max_dim);
        a = matrix_alloc(current_size, new_size);
        current_size = new_size;

        for(k = 0; k < a.rows; k++)
            for(j = 0; j < a.cols; j++)
                set(a, k, j, -32 + (rand() % 64));
        
        matrix_print(in_stream, a);

        if(i == 0)
            current_product = a;
        else
        {
            matrix new_current = matrix_mult(current_product, a);
            matrix_free(current_product);
            current_product = new_current;
            matrix_free(a);
        }
    }

    matrix_print(out_stream, current_product);

    fclose(out_stream);
    fclose(in_stream);

    return 0;
}


