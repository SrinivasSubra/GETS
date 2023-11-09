#include "gets.h"
/* Used by gets_nnreg for the NNREG problem.
 Update the QR factorization when a new column is added.
  C is the QR factorized version of the submatrix Ctilde in the form of VR matrix, where for householder vectors v, v(1) = 1 is not stored. (See Algorithm 5.1.1, Golub & Van Loan, 4th ed, page 236.)
 Assumes s columns of C are already in VR form.
 Adds [lambda*A(:,j); 1] as a new column to C, updates householder vectors v, and upper triangular part R, beta and the right hand side vector b. */
void gets_qrupdate_reg(double *C, double *b, double *beta, csi s, const char *A, const csi *diag, csi j, csi m, double lambda)
{
    csi i, k ;
    double *z ;
    z = C+(m+1)*s ; /*points to start of C(:,s+1)*/
    
    for ( i = 0 ; i < m ; i++ )
    {   z[i] = (double) lambda * A[m*j + i]/ diag[j] ;  /* Csub(1:m,s+1)=lambda*A(:,j)/diag(j) */
    }
    z[m] = 1 ; /* Csub(m+1,s+1) = 1 */
    
    /* for NNREG, applyhouse and makehouse remain unchanged, just need to pass m+1 instead of m*/
    for (k = 0 ; k < s ; k++) gets_applyhouse(C, k, m+1, beta[k], z) ; /* apply all the previous householders on the new column */
    gets_makehouse(z+s, beta+s, m+1-s) ; /* compute the householder V(s+1), beta(s+1) for C(s+1:m+1,s+1) */
    gets_applyhouse(C, s, m+1, beta[s], b) ; /* apply V(s+1), beta(s+1) to RHS b(s+1:m+1) */
    
}

  

