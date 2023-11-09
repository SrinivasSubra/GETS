#include "gets.h"

csi gets_argmaxw( double *w, char *P, csi n)   /* finds maxind such that w[maxind]= max{w(i), i in the passive set Z}. P(Z) is zeros */
{
    double max = -INFINITY ;
    csi maxind = -1, i ;   /* if maxind is returned as -1, then Z must have been empty */
    
    for(i = 0 ; i < n ; i++)
    {
        if(P[i]==0)   /* i is in Z */
        {
            if(max < w[i])
            {
                max = w[i] ;
                maxind = i ;
            }
        }
    }
    
    return maxind ;
}
