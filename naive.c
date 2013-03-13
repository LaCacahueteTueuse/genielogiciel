
#include "matrix.h"
#include "mult.h"

int main(int argc, char *argv[])
{
    matrix a, b, c;

    a = matrix_read();
    b = matrix_read();
    c = matrix_mult(a,b);
    matrix_print(stdout, c);
    
    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    return 0;
}

