#include "matrix.h"

#include <stddef.h>
#include <stdio.h>  // pour printf, scanf
#include <stdlib.h> // pour malloc, free
#include <string.h> // pour memcpy

// Alloue une matrice
matrix matrix_alloc(int rows, int cols)
{
    matrix m;

    m.rows = rows;
    m.cols = cols;
    m.trows = rows;
    m.tcols = cols;
    m.r_offset = 0;
    m.c_offset = 0;

    m.orig_rows = rows;
    m.orig_cols = cols;

    m.coef = malloc(m.rows*sizeof(matval*));

    int i = 0;
    while(i < m.rows)
    {
	    m.coef[i] = malloc(m.cols*sizeof(matval));
        i++;
    }

    return m;
}

// Alloue une matrice avec des lignes virtuelles en plus
matrix matrix_alloc_virtual(int trows, int tcols, int rows, int cols)
{
     matrix m = matrix_alloc(trows, tcols);
     m.rows = rows;
     m.cols = cols;
     return m;
}

// Initialise une matrice avec des zéros
void matrix_fill(matrix m)
{
   int i, j;

   for(i = 0; i < m.rows; i++)
      for(j = 0; j < m.cols; j++)
	 m.coef[i][j] = 0;
}

// Alloue une matrice initialisée à zéro
matrix matrix_alloc_zero(int rows, int cols)
{
    matrix m;

    m = matrix_alloc(rows, cols);
    matrix_fill(m);

    return m;
}

// Libère une matrice
void matrix_free(matrix m)
{
    int i;

    for(i = 0; i < m.rows; i++)
	    free(m.coef[i]);
    free(m.coef);
}

// Copie une matrice
// (seulement ses coefficients entre
//  r_offset <= i < r_offset + rows
//  c_offset <= j < c_offset + cols)
matrix matrix_copy(matrix m)
{
    matrix n;
    int i;

    n = matrix_alloc(m.rows, m.cols);
    for(i = m.r_offset; i < m.r_offset + m.rows; i++)
	memcpy(m.coef[i] + m.c_offset, n.coef[i], m.cols * sizeof(matval));

    return n;
}

// Accède au coefficient (i,j)
matval* at(matrix m, int i, int j)
{
    if(i >= m.rows || j >= m.cols)
        printf("Warning, index out of bounds");
    else
        return &m.coef[m.r_offset + i][m.c_offset + j];
    return 0;
}

// Accède au coefficient (i,j) (raccourci)
matval get(matrix m, int i, int j)
{
//printf("get : i = %d, j = %d\n",i,j);
    if (i >= m.trows || j >= m.tcols)
        return 0;
    else
        return *at(m, i, j);
}

// Change le coefficient (i,j) (raccourci)
void set(matrix m, int i, int j, matval v)
{
    //printf("set : i = %d, j = %d dans mat de taille %d x %d \n",i,j,m.rowsr_offset,m.colsc_offset);
    if (i >= m.trows || j >= m.tcols) 
	    return ; 
    else *at(m, i, j) = v;
}

// Affiche la matrice sur la sortie standard
void matrix_print(FILE* out_chan, matrix m)
{
    int i, j;

    fprintf(out_chan, "%d %d\n", m.rows, m.cols);
    for(i = 0; i < m.rows; i++)
    {
        for(j = 0; j < m.cols; j++)
            fprintf(out_chan, "%d ", get(m, i, j));
        fprintf(out_chan, "\n");
    }
}

// Assure que tous les coefs sont entre 0 et MATRIX_MOD - 1
void matrix_mod(matrix m)
{
    int i,j;
    for(i = 0; i < m.rows; i++)
        for(j = 0; j < m.cols; j++)
            set(m, i, j, modulo(get(m,i,j)));
}

// Lit une matrice sur l'entrée standard
// Format : rows cols puis la matrice
matrix matrix_read()
{
    return matrix_read_from(stdin);
}

// Lit une matrice depuis un fichier arbitraire
matrix matrix_read_from(FILE* in_chan)
{
    matrix m;
    int i, j;
   
    fscanf(in_chan, "%d", &m.rows);
    fscanf(in_chan, "%d", &m.cols);
    
    m = matrix_alloc(m.rows, m.cols);

    for(i = 0; i < m.rows; i++)
        for(j = 0; j < m.cols; j++)
            fscanf(in_chan, "%d", &m.coef[i][j]);


    return m;
}

// Renvoie la sous-matrice désignée
matrix sub_matrix(matrix m, int r_offset, int c_offset,
      int trows, int tcols, int rows, int cols)
{
    if(m.r_offset + r_offset + trows > m.orig_rows)
	printf("sub_matrix : critical rows overflow\n");
    if(m.c_offset + c_offset + tcols > m.orig_cols)
	printf("sub_matrix : critical cols overflow\n");

    m.r_offset += r_offset;
    m.c_offset += c_offset;
    m.trows = trows;
    m.tcols = tcols;
    m.rows = rows ;
    m.cols = cols ;
    return m;
}


// Modulo
int modulo(int n)
{
    while((n = ((n + MATRIX_MOD) % MATRIX_MOD)) < 0);
    return n;
}


