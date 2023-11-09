#include "gets.h"
/* matvec: matrix vector multiplication.
computes w = w - A*x ; w is passed in as w = d , A is a dense matrix, x is a sparse vector stored as a CSparse cs struct */
void gets_matvec(const char *A, const cs*x, double *w, csi m)
{  
   csi i, j, p, *xi, *xp ;
   double *xx ; 
   xi = x->i ; xp = x->p ;
   xx = x->x ;
   
    for(p = xp[0] ; p < xp[1] ; p++)  /* xp[0] is 0, xp[1] is the sparsity s. Loop runs through the non-zero values in x */
    {
        j = xi[p] ; /*index of current non-zero value */
        for(i = 0; i < m; i++) /*w = w - x(j)*A(:,j)*/
        {
            w [i] -= A[j*m + i]*xx[p] ; /*w(i) = w(i) - A(i,j)*x(j)*/
        }
    }

}

