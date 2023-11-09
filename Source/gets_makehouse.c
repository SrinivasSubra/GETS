 #include "gets.h"
/* construct a Householder vector v and beta for the transformation
 H = I - beta*v*v', so that H*x is all zero except for the 1st entry.
 H*x = s*e1, where s = norm(x).
 [v,beta] = makehouse(x,n), overwrite a length n vector x with v,
 See Algo 5.1.1, Golub & Van Loan,4th ed.pg236.
 v(1) = 1 is not stored, but overwritten with s = norm(x).
 */     
void gets_makehouse (double *x, double *beta, csi n)
{
    double s, sigma = 0 ;
    csi i ;

    for (i = 1 ; i < n ; i++) sigma += x [i] * x [i] ;
    if (sigma == 0)
    {
        s = fabs (x [0]) ;                  /* s = |x(0)| */
        (*beta) = (x [0] <= 0) ? 2 : 0 ;
        x [0] = s ;
    }
    else
    {
        s = sqrt (x [0] * x [0] + sigma) ;  /* s = norm (x) */
        x [0] = (x [0] <= 0) ? (x [0] - s) : (-sigma / (x [0] + s)) ;
        (*beta) = (2 * x[0] * x[0]) / (sigma + x[0] * x[0]) ;
        for (i = 1 ; i < n ; i++) x[i] /= x[0] ; /* normalize */
        x[0] = s ;
    }
    
}


