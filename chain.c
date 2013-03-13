#include "chain.h"

#include "mult.h"
#include <stdlib.h>

// memo et splits sont des tableaux triangulaires
// suppose que memo est initialement rempli à -1.
int cost(matrix* mat, int **memo, int **splits, int begin, int end)
{
   if(begin + 1 == end)
       return 0;
   if(memo[begin][end] != -1)
      return memo[begin][end];
   if(begin + 2 == end)
       return memo[begin][end] =
              mat[begin].rows * mat[begin].cols * mat[begin+1].cols;
   
   int i, mincost, imin;
   for(i = begin + 1; i < end; i++)
   {
        int curcost = cost(mat, memo, splits, begin, i) 
                    + cost(mat, memo, splits, i, end)
                    + mat[begin].rows * mat[i].rows * mat[end-1].cols;
        if(curcost < mincost || i == begin + 1)
        {
            imin = i;
            mincost = curcost;
        }
   }
   
   splits[begin][end] = imin;
   return memo[begin][end] = mincost;
}

// renvoie le produit de deux matrices, en libérant les deux arguments
matrix mult_and_free(matrix a, matrix b)
{
    // TODO : remplacer matrix_mult par Strassen !
    matrix res;
    res = matrix_mult(a, b);
    matrix_free(a);
    matrix_free(b);
    return res;
}

// attention : cette fonction détruit le tableau mat !
matrix prod(matrix* mat, int **splits, int begin, int end)
{
    if(begin + 1 == end)
        return mat[begin];
    if(begin + 2 == end) 
        return mult_and_free(mat[begin], mat[begin+1]);

    return mult_and_free(
            prod(mat, splits, begin, splits[begin][end]),
            prod(mat, splits, splits[begin][end], end));
}

void print_solution(int begin, int end, int** splits)
{
    if(begin + 1 == end)
        printf("M%d", begin+1);
    else if(begin + 2 == end)
        printf("(M%d*M%d)", begin+1, begin+2);
    else
    {
        printf("(");
        print_solution(begin, splits[begin][end], splits);
        printf("*");
        print_solution(splits[begin][end], end, splits); 
        printf(")");
    }
}

matrix chain_product(int size, matrix* mat)
{
    int **memo = malloc((size+1)*sizeof(int*));
    int **splits = malloc((size+1)*sizeof(int*));

    int i;
    for(i = 0; i < size+1; i++)
    {
        // idée d'optimisation : allouer 2 fois moins de mémoire
        // en n'allouant que la partie au dessus de la diagonale
        // il faut modifier le code des autres fonction en conséquence
        memo[i] = malloc(size*sizeof(int));
        splits[i] = malloc(size*sizeof(int));

        int j;
        for(j = 0; j < size+1; j++)
            memo[i][j] = -1;
    }
    
    cost(mat, memo, splits, 0, size);

    matrix result = prod(mat, splits, 0, size);

    print_solution(0, size, splits);
    printf("\n");
    // TODO : free memo & splits
    return result;
}

