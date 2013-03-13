
#include "matrix_proxy.h"
#include "matrix.h"

// Addition de matrices
matrix_proxy add_p(matrix_proxy* a, matrix_proxy* b)
{
    matrix_proxy mp;
    mp.nt = T_SUM;
    mp.left = a;
    mp.right = b;

    return mp;
}

// Soustraction de matrices
matrix_proxy sub_p(matrix_proxy* a, matrix_proxy* b)
{
    matrix_proxy mp;
    mp.nt = T_DIFF;
    mp.left = a;
}

// Multiplication de matrices
matrix_proxy mult_p(matrix_proxy* a, matrix_proxy* b)
{

}

// Multiplication par un scalaire
matrix_proxy scal_p(matval scal, matrix_proxy* a)
{

}

// Force les opérations
matrix_proxy force_p(matrix_proxy* p)
{

}

// Renvoie la vraie matrice représentée par le proxy
// (demande de forcer si c'est pas fait)
matrix get_m(matrix_proxy* p)
{

}

