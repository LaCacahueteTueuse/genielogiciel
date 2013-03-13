
#include "matrix.h"

int main(int argc, char **argv)
{
    if(argc <= 1)
    {
        printf("no filename provided.\n");
        return 2;
    }

    FILE* in = fopen(argv[1], "r");
    if(in == 0)
    {
        printf("unable to open the file %s\n", argv[1]);
        return 2;
    }

    matrix a = matrix_read_from(in);
    fclose(in);
    matrix b = matrix_read();

    if(a.rows == b.rows && a.cols == b.cols)
    {
        int i, j;
        for(i = 0; i < a.rows; i++)
            for(j = 0; j < a.cols; j++)
                if(get(a,i,j) - get(b,i,j) % MATRIX_MOD)
                {
                    printf("%d %d\n", i, j);
                    return 1;
                }
    }
    else
        return 1;

    matrix_free(a);
    matrix_free(b);
    return 0;
}

