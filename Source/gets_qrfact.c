#include "gets.h"
/* compute the QR factorization column by column by repeatedly using qr_update. The columns of A that form the submatrix are specified by the index set of the sparse vector x of size s.
   Upon completion, C will be the QR factorized version of the submatrix in the form of a VR matrix, where for householder vectors v, v(1) = 1 is not stored. (See Algorithm 5.1.1, Golub & Van Loan, 4th ed, page 236.)
 b = d on input, updated right hand side upon completion.
 */
void gets_qrfact(double *C, double *b, double *beta, csi s, const char *A, const csi *diag, csi m, cs *x)
{
    csi i, p, *xi;
    xi = x->i ;

    for (p = 0 ; p < s ; p++) /*qrupdate adding one column at a time */
    {
        i = xi[p] ; /*add this column and update*/
        gets_qrupdate(C, b, beta, p, A, diag, i, m) ;
    }
        
}

