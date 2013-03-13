
#include "mult.h"

#include <stdio.h>

// Multiplication naïve
matrix matrix_mult(matrix a, matrix b)
{
    matrix m;
    size_t i, j, k;
    matval s;

    if(a.cols != b.rows)
    {
        printf("Warning : invalid sizes in matrix_mult");
        m.cols = 0;
        m.rows = 0;
        return m;
    }

    m = matrix_alloc_zero(a.rows, b.cols);
    for(i = 0; i < m.rows; i++)
        for(j = 0; j < m.cols; j++)
        {
            s = 0;
            for(k = 0; k < a.cols; k++)
                s += (get(a, i, k) * get(b, k, j)) % MATRIX_MOD;
            set(m, i, j, modulo(s));
        }

    return m;
}

