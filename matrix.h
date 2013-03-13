
#ifndef INCLUDED_MATRIX_H
#define INCLUDED_MATRIX_H

#include <stdio.h>

#define MATRIX_MOD 65536


// Type pour les coefficients des matrices
// Il suffit de changer ce typedef
// pour passer à des flottants, des long, etc
typedef int matval;

// Type des matrices
struct matrix
{
    matval** coef;

    int rows;
    int cols;
    int tcols;
    int trows;
    int r_offset;
    int c_offset;

    int orig_rows;
    int orig_cols;
};


typedef struct matrix matrix;

// Alloue une matrice
matrix matrix_alloc(int rows, int cols);

// Alloue une matrice avec des lignes virtuelles en plus
matrix matrix_alloc_virtual(int trows, int tcols, int rows, int cols);

// Initialise une matrice avec des zéros
void matrix_fill(matrix m);

// Alloue une matrice initialisée à zéro
matrix matrix_alloc_zero(int rows, int cols);

// Libère une matrice
void matrix_free(matrix m);

// Copie une matrice
// (seulement ses coefficients entre
//  r_offset <= i < r_offset + rows
//  c_offset <= j < c_offset + cols)
matrix matrix_copy(matrix m);

// Accède au coefficient (i,j) (sous forme d'un pointeur)
matval* at(matrix m, int i, int j);

// Accède au coefficient (i,j) (raccourci)
matval get(matrix m, int i, int j);

// Change le coefficient (i,j) (raccourci)
void set(matrix m, int i, int j, matval v);

// Affiche la matrice dans un fichier
void matrix_print(FILE* out_chan, matrix m);

// Lit une matrice sur l'entrée standard
// Format : rows cols puis la matrice
matrix matrix_read();

// Lit une matrice depuis un fichier arbitraire
matrix matrix_read_from(FILE* in_chan);

// Assure que tous les coefs sont entre 0 et MATRIX_MOD - 1
void matrix_mod(matrix m);

// Renvoie la sous-matrice désignée
matrix sub_matrix(matrix m, int r_offset, int c_offset, int trows,
	 		int tcols, int null_rows, int null_cols);

// Modulo
int modulo(int);


#endif // INCLUDED_MATRIX_H

