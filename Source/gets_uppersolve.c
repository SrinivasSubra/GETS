 #include "gets.h"
/* solve Rx = b(1:s), where R is stored as the upper triangular part of a VR matrix C, i.e., R = triu(C(1:s,1:s)).
   m is the number of rows of C.
   x = b on input, solution upon completion. */
void gets_uppersolve (const double *C, csi m, csi s, double *x)
{
    csi i, j ;
    
    /* solve the upper triangular system by backward substitution */
    for (j = s-1 ; j >= 0 ; j--)
    {
        x [j] /= C[m*j+j] ;
        for (i = 0 ; i < j ; i++)
        {
            x [i] -= C[m*j+i]*x[j] ;
        }
    }
    
}


