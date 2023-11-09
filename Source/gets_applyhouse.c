#include "gets.h"
/* apply the jth householder vector v to x. (j can be 0, since C language uses zero based indexing)
  Replace x by Hj*x = (I - beta*v*v')x = x - beta(v'*x)v
   v is stored as C(j+1:m,j), v(1) = 1 is not stored.
 Applied to x(j:m).
 example: gets_applyhouse(C, s, m, beta[s], b) ; */
void gets_applyhouse (const double *C, csi j, csi m, double beta, double *x)
{
    csi i, k = j*m ;
    double tau = x[j] ;   /* first term in tau = v'*x is 1*x[j] since v(1) = 1 */

    for (i = j+1 ; i < m ; i++)   /* tau = v'*x */
    {
        tau += C[k+i] * x [i] ;
    }
    tau *= beta ;   /* tau = beta*(v'*x) */
    x[j] -= tau ;   /* first term is 1*tau since v(1) = 1 */
    for (i = j+1 ; i < m ; i++)   /* x = x - v*tau */
    {
        x[i] -= C[k+i] * tau ;
    }
    
}



























                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                
