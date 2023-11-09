#include "gets.h"
/* update the QR factorization when a new column is added.
  C is the QR factorized version of the submatrix in the form of VR matrix, where for householder vectors v, v(1) = 1 is not stored. (See Algorithm 5.1.1, Golub & Van Loan, 4th ed, page 236.)
 Assumes s columns of C are already in VR form.
 Adds column j of A, updates householder vectors v, and upper triangular part R, beta and the right hand side vector b. */
void gets_qrupdate(double *C, double *b, double *beta, csi s, const char *A, const csi *diag, csi j, csi m)
{
    csi i, k ;
    double *z ;
    z = C+m*s ; /*points to start of C(:,s+1)*/
    
    for ( i = 0 ; i < m ; i++ )
    {   z[i] = (double)A[m*j + i]/ diag[j] ;  /* Csub(:,s+1)=A(:,j)/diag(j) */
    }
            
    for (k = 0 ; k < s ; k++) gets_applyhouse(C, k, m, beta[k], z) ; /* apply all the previous householders on the new column */
    gets_makehouse(z+s, beta+s, m-s) ; /* compute the householder V(s+1), beta(s+1) for C(s+1:m,s+1) */
    gets_applyhouse(C, s, m, beta[s], b) ; /* apply V(s+1), beta(s+1) to RHS b(s+1:m) */
    
}

  

