
#ifndef INCLUDED_MATRIX_PROXY_H
#define INCLUDED_MATRIX_PROXY_H

#include "matrix.h"

enum node_type
{
     T_MATRIX,
     T_PROD,
     T_SUM,
     T_DIFF,
     T_SCAL_PROD
};
typedef enum node_type node_type;

struct matrix_proxy
{
     node_type nt;
     matval scal;
     matrix_proxy* left;
     matrix_proxy* right;
};
typedef struct matrix_proxy matrix_proxy;

/* Les opérations qui suivent sont paresseuses,
 * sauf mention du contraire. */

// Addition de matrices
matrix_proxy add_p(matrix_proxy* a, matrix_proxy* b);

// Soustraction de matrices
matrix_proxy sub_p(matrix_proxy* a, matrix_proxy* b);

// Multiplication de matrices
matrix_proxy mult_p(matrix_proxy* a, matrix_proxy* b);

// Multiplication par un scalaire
matrix_proxy scal_p(matval scal, matrix_proxy* a);

// Force les opérations
matrix_proxy force_p(matrix_proxy* p);

// Renvoie la vraie matrice représentée par le proxy
// (demande de forcer si c'est pas fait)
matrix get_m(matrix_proxy* p);

#endif // INCLUDED_MATRIX_PROXY_H

