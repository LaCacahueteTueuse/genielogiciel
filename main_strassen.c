
#include "matrix.h"
#include "strassen.h"
#include <stdio.h>

int max(int a, int b)
{
    return (a > b ? a : b);
}

int main()
{
    matrix a, b, c, d;

    a = matrix_read();
    b = matrix_read();
    c = matrix_alloc(a.rows, b.cols);
    d = matrix_alloc(max(a.cols, a.rows)+100,
	    	     max(b.cols, b.rows)+100);

    strassen(a,b,c,d);
    matrix_print(stdout, c);

    return 0;
}


