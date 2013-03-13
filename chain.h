#ifndef INCLUDED_CHAIN_H
#define INCLUDED_CHAIN_H

#include "matrix.h"

// Calcule le produit de 'size' matrices à coût minimal
matrix chain_product(int size, matrix* mat);

// Vérifie que le produit est bien légal
int valid_chain(int size, matrix* mat);

#endif // INCLUDED_CHAIN_H

