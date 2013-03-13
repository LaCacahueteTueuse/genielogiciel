#include "matrix.h"
#include "mult.h"

/*
m et n inchangé
r = m + n
*/
void add (matrix m, matrix n, matrix r){
    int i,j;
    for(i = 0; i < r.rows; i++){
        for(j = 0; j < r.cols; j++)
            set(r, i, j,modulo(get(m,i,j)+get(n,i,j)));
    }
}

/*
m et n inchangé
r = m - n
*/
void sous(matrix m, matrix n, matrix r){
    int i,j;
    for(i = 0; i < r.rows; i++){
        for(j = 0; j <  r.cols; j++)
          set(r, i, j,modulo(get(m,i,j)-get(n,i,j)));
    };
}

/*
m inchangé
renvoie n = m
Faire des copy(x,a) que si (x.trows != a.trows)||(x.tcols != a.tcols)  
*/
void copy(matrix m, matrix n){
    int i,j;
    for(i = 0; i < n.rows; i++){
        for(j = 0; j <  n.cols; j++)
        {
          set(n, i, j, get(m,i,j));
        };
    };
}

void zero(matrix m){
    int i,j;
    for(i = 0; i < m.rows; i++){
        for(j = 0; j <  m.cols; j++)
        {
          set(m, i, j, 0);
        };
    };
}

//int max (int x,int y){if (x > y) {return x;} else {return y;};}

/*
m et n inchangé
a = m x n
b changé (utilisé comme mémoire de taille max(m.rows,n.rows)*max(n.cols,m.cols))
*/	
void strassen(matrix m,matrix n,matrix a,matrix b){
  if ((m.tcols <= 1)||(m.trows <= 1)||(n.tcols <= 3)) {
	//si une des dimension est de taille inférieur à 1
	//on effectue une multiplication naive
        int i,j,k;
        matval s;
        for(i = 0; i < m.rows; i++)
            for(j = 0; j < n.cols; j++)
            {
                s = 0;
                for(k = 0; k < m.cols; k++)
                   s += (get(m, i, k) * get(n, k, j)) % MATRIX_MOD;
                set(a, i, j, modulo(s));
            }
    }
    else{ 
        matrix m11, m12, m21, m22;
        matrix n11, n12, n21, n22;
        matrix a11, a12, a21, a22;
        matrix b11, b12, b21, b22;

        int lm = 0,cm = 0,cn = 0;
	//si une des dimension est impaire
	//alors on étend virtuellement la dimension de x.rows ou x.cols
        if (m.rows % 2 == 1)
          {if (m.rows > m.trows) {lm = -1;} else {lm = 1;};};
        if (m.cols % 2 == 1)
          {if ((m.cols > m.tcols)&&(n.rows > n.trows)) {cm = -1;} else {cm = 1;};};
        if (n.cols % 2 == 1)
          {if (n.cols > n.tcols) {cn = -1;} else {cn = 1;};};

        int mrows2 = (m.rows + lm)/2;
        int mcols2 = (m.cols + cm)/2;
        int nrows2 = mcols2;
        int ncols2 = (n.cols + cn)/2;
        int arows2 = mrows2;
        int acols2 = ncols2;
	int mtrows2, mtcols2, ntrows2, ntcols2, atrows2, atcols2;

	//Création des sous matrices de m 
	if (m.trows <= mrows2) {mtrows2 = m.trows;} else {mtrows2 = mrows2;};
	if (m.tcols <= mcols2) {mtcols2 = m.tcols;} else {mtcols2 = mcols2;};
        m11 = sub_matrix(m,0,0,mtrows2,mtcols2,mrows2,mcols2);
        m12 = sub_matrix(m,0,m11.tcols,m11.trows,m.tcols - m11.tcols,mrows2,mcols2);
        m21 = sub_matrix(m,m11.trows,0,m.trows - m11.trows,m11.tcols,mrows2,mcols2);
        m22 = sub_matrix(m,m11.trows,m11.tcols,m.trows - m11.trows,m.tcols - m11.tcols,mrows2,mcols2);

	//Création des sous matrices de n 
	if (n.trows <= nrows2) {ntrows2 = n.trows;} else {ntrows2 = nrows2;};
	if (n.tcols <= ncols2) {ntcols2 = n.tcols;} else {ntcols2 = ncols2;};
        n11 = sub_matrix(n,0,0,ntrows2,ntcols2,nrows2,ncols2);
        n12 = sub_matrix(n,0,n11.tcols,n11.trows,n.tcols - n11.tcols,nrows2,ncols2);
        n21 = sub_matrix(n,n11.trows,0,n.trows - n11.trows,n11.tcols,nrows2,ncols2);
        n22 = sub_matrix(n,n11.trows,n11.tcols,n.trows - n11.trows,n.tcols - n11.tcols,nrows2,ncols2);

	//Création des sous matrices de a 
	if (a.trows <= arows2) {atrows2 = a.trows;} else {atrows2 = arows2;};
	if (a.tcols <= acols2) {atcols2 = a.tcols;} else {atcols2 = acols2;};
        a11 = sub_matrix(a,0,0,atrows2,atcols2,arows2,acols2);
        a12 = sub_matrix(a,0,a11.tcols,a11.trows,a.tcols - a11.tcols,arows2,acols2);
        a21 = sub_matrix(a,a11.trows,0,a.trows - a11.trows,a11.tcols,arows2,acols2);
        a22 = sub_matrix(a,a11.trows,a11.tcols,a.trows - a11.trows,a.tcols - a11.tcols,arows2,acols2);

	// Découpage des B			
        b11 = sub_matrix(b,0,0,n21.trows,n21.tcols,n21.rows,n21.cols);
	zero(b11);
        add(n21,n22,b11);

        b12 = sub_matrix(b,0,b11.tcols,m12.trows,m12.tcols,m12.rows,m12.cols);// retouche
	zero(b12);
        sous(m12,m22,b12);

	b21 = sub_matrix(b,max(b11.trows,b12.trows),0,b12.rows, b11.cols,b12.rows, b11.cols);
	zero(b21);
        b22 = sub_matrix(b,max(b11.trows,b12.trows),max(b21.tcols,b11.tcols),b.trows - max(b11.trows,b12.trows),b.tcols - max(b21.tcols,b11.tcols),b.rows - max(b11.trows,b12.trows),b.cols - max(b21.tcols,b11.tcols));
	zero(b22);
        strassen(b12,b11,b21,b22);
	copy(b21,a11);//a11 = X7

        b12 = sub_matrix(b,0,b11.tcols,m11.trows,m11.tcols,m11.rows,m11.cols);
	zero(b12);
        add(m11,m12,b12);

        b21 = sub_matrix(b,b12.trows,0,b12.rows,n22.cols,b12.rows,n22.cols);// peut mettre b11 et prendre b22 plus grand
	zero(b21);
        b22 = sub_matrix(b,max(b11.trows,b12.trows),max(b21.tcols,b11.tcols),b.trows - max(b11.trows,b12.trows),b.tcols - max(b21.tcols,b11.tcols),b.rows - max(b11.trows,b12.trows),b.cols - max(b21.tcols,b11.tcols));
	zero(b22);
        strassen(b12,n22,b21,b22);
        copy(b21,a12);//a12 = X5
	sous(a11,b21,a11);//a11 = - X5 + X7

        b11 = sub_matrix(b,0,0,n11.trows,n11.tcols,n11.rows,n11.cols);
	zero(b11);
        sous(n21,n11,b11);

        b21 = sub_matrix(b,max(b11.trows,b12.trows),0,m22.rows,b11.cols,m22.rows,b11.cols);
	zero(b21);
        b22 = sub_matrix(b,max(b11.trows,b12.trows),max(b21.tcols,b11.tcols),b.trows - max(b11.trows,b12.trows),b.tcols - max(b21.tcols,b11.tcols),b.rows - max(b11.trows,b12.trows),b.cols - max(b21.tcols,b11.tcols));
	zero(b22);
        strassen(m22,b11,b21,b22);
        copy(b21,a21);//a21 = X4

	add(a11,b21,a11);//a11 = X4 - X5 + X7

	b11 = sub_matrix(b,0,0,n11.trows,n11.tcols,n11.rows,n11.cols);
	zero(b11);
        add(n11,n12,b11);

        b12 = sub_matrix(b,0,b11.tcols,m11.trows,m11.tcols,m11.rows,m11.cols);
	zero(b12);
        sous(m21,m11,b12);

        b21 = sub_matrix(b,max(b11.trows,b12.trows),0,b12.rows, b11.cols,b12.rows, b11.cols);
	zero(b21);
       	b22 = sub_matrix(b,max(b11.trows,b12.trows),max(b21.tcols,b11.tcols),b.trows - max(b11.trows,b12.trows),b.tcols - max(b21.tcols,b11.tcols),b.rows - max(b11.trows,b12.trows),b.cols - max(b21.tcols,b11.tcols));
	zero(b22);
        strassen(b12,b11,b21,b22);
        copy(b21,a22);//a22 = X6

        b11 = sub_matrix(b,0,0,n12.trows,n12.tcols,n12.rows,n12.cols);
	zero(b11);
        sous(n12,n22,b11);

        b21 = sub_matrix(b,b11.trows,0,m11.rows, b11.cols,m11.rows, b11.cols);
	zero(b21);
       	b22 = sub_matrix(b,max(b11.trows,b12.trows),max(b21.tcols,b11.tcols),b.trows - max(b11.trows,b12.trows),b.tcols - max(b21.tcols,b11.tcols),b.rows - max(b11.trows,b12.trows),b.cols - max(b21.tcols,b11.tcols));
	zero(b22);
        strassen(m11,b11,b21,b22);
	b21 = sub_matrix(b21,0,0,m11.trows, b11.tcols,m11.rows, b11.cols);//b21 = X3
        add(a12,b21,a12);//a12 = X3 + X5 = P12
        add(a22,b21,a22);//a22 = X3 + X6

        b12 = sub_matrix(b,0,b11.tcols,m21.trows,m21.tcols,m21.rows,m21.cols);
	zero(b12);
        add(m21,m22,b12);

        b21 = sub_matrix(b,b11.trows,0,b12.rows, n11.cols,b12.rows, n11.cols);
	zero(b21);
        b22 = sub_matrix(b,max(b11.trows,b12.trows),max(b21.tcols,b11.tcols),b.trows - max(b11.trows,b12.trows),b.tcols - max(b21.tcols,b11.tcols),b.rows - max(b11.trows,b12.trows),b.cols - max(b21.tcols,b11.tcols));
	zero(b22);
        strassen(b12,n11,b21,b22);//b21 = X2 
	b21 = sub_matrix(b21,0,0,b12.trows, n11.tcols,b21.rows, b21.cols);

        add(a21,b21,a21);//a21 = X2 + X4 = P21
        sous(a22,b21,a22);//a22 = - X2 + X3 + X6

 	b11 = sub_matrix(b,0,0,n11.trows,n11.tcols,n11.rows,n11.cols);
	zero(b11);
        add(n11,n22,b11);

        b12 = sub_matrix(b,0,b11.tcols,m11.trows,m11.tcols,m11.rows,m11.cols);
	zero(b12);
        add(m11,m22,b12);

        b21 = sub_matrix(b,max(b11.trows,b12.trows),0,b12.rows, b11.cols,b12.rows, b11.cols);
	zero(b21);
        b22 = sub_matrix(b,max(b11.trows,b12.trows),max(b21.tcols,b11.tcols),b.trows - max(b11.trows,b12.trows),b.tcols - max(b21.tcols,b11.tcols),b.rows - max(b11.trows,b12.trows),b.cols - max(b21.tcols,b11.tcols));
	zero(b22);
        strassen(b12,b11,b21,b22);
	b21 = sub_matrix(b21,0,0,b12.trows, b11.tcols,b21.rows, b21.cols);//b21 = X1

        add(a22,b21,a22);//a22 = P22
        add(a11,b21,a11);//a11 = P11
    }
} 

