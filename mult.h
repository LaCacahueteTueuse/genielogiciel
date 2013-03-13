
#ifndef INCLUDED_MULT_H
#define INCLUDED_MULT_H

#include "matrix.h"

// Multiplication naïve
matrix matrix_mult(matrix a, matrix b);

// Multiplication par Strassen
// en supposant que la taille est une puissance de 2
matrix strassen_2n(matrix a, matrix b);

#endif // INCLUDED_MULT_H

