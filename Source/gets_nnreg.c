#include "gets.h"
/* gets_nnreg: solve a non negative regularization (NNREG) problem via the Lawson Hanson algorithm.
   NNREG: min (∥v∥_1)^2 + λ^2 (∥d − Cv∥_2)^2 subject to v ≥ 0
   Input treedata struct D contains the sparse representation of the data allowing for reduced storage and large asymptotic speed ups. d is the right hand side vector. lambda is the regularization parameter.
   return x, the sparse vector solution */

#define FREE_WORK \
{                               \
cs_spfree (xscale) ;          \
cs_free (Csub) ;             \
cs_free (beta) ;             \
cs_free (b) ;                \
cs_free (w) ;                \
cs_free (resid) ;            \
cs_free (P) ;        \
}

#define FREE_ALL \
{                               \
    FREE_WORK ;                 \
    cs_spfree(x) ;          \
                 \
}

cs *gets_nnreg (const treedata *D, const double *d, double lambda)
{
    char *A ; csi *diag ;
    A = D->A ; diag = D->diag ;
    double alpha, val, tol, sumx ;
    csi i, p, t, m, n, s, iter, itmax, smax ;
    m = D->m ; n = D->n ;
    iter = 0, itmax = 1000, s = 0, smax = 64 ; /* s is the sparsity level, set smax initially as 64 */
    tol = 4.1817e-10 ; /* tol = 10*eps*norm(C,1)*length(C); */
  
    /* workspace variables that need to be freed later in FREE_WORK are initialized here as NULL */
    cs *x, *xscale = NULL ;
    char *P = NULL ;
    double *Csub = NULL, *beta = NULL, *b = NULL, *resid = NULL, *w = NULL ;
    x = cs_spalloc (n, 1, smax, 1, 0) ;  /* x is the sparse solution vector of size n */
    xscale = cs_spalloc (n, 1, smax, 1, 0) ; /* x scaled with diag for gets_matvec */
    if(!x || !xscale){FREE_ALL ; return(NULL) ;}
    csi *xi, *xscalei, *xp, *xscalep ;
    double *xx, *xscalex ;
    
    xp = x->p ; xscalep = xscale->p ;
    xi = x->i ; xscalei = xscale->i ;
    xx = x->x ; xscalex = xscale->x ;
    
    xp[0] = 0 ; xscalep[0] = 0 ;
    P = cs_calloc (n, sizeof(char)) ;  /* P is a binary vector to keep track of active set, P(i)=1 iff i is in active set */
    Csub = cs_malloc ((m+1)*smax, sizeof(double)) ; /* Csub is the VR matrix that stores householder vectors V below diagonal and upper triangular R with s columns */
    beta = cs_malloc (smax, sizeof(double)) ; /* collection of beta(i) corresponding to the householder vectors V(i) */
    b = cs_malloc (m+1, sizeof(double)) ;   /* right hand side that changes as householders are applied */
    resid = cs_malloc (m, sizeof(double)) ;  /* resid = d - C*x */
    double *xls = resid ; /* pointer enables using resid as workspace for gets_uppersolve */
    w = cs_malloc (n, sizeof(double)) ;   /* w = C'*resid */
    
    if(!P || !Csub || !beta || !b || !resid || !w )   /* alloc failed, free everything and return NULL */
    {
        FREE_ALL ;
        return (NULL) ;
    }
    
    for(i = 0 ; i < m ; i++)  /* need b = [lambda*d;0] on entry to gets_qrupdate_reg for the first time */
    {
        b[i] = lambda*d[i] ;
        
    }
    b[m] = 0 ;
    
    gets_treemult (D, d, w) ;  /* initialize w = A'*d */
    
    for(i = 0 ; i < n ; i++)    /* scaling after treemult to make w = lambda^2(C'd) */
    {
        w[i] /= diag[i] ;
        w[i] *= lambda * lambda ;
    }
    
    csi success, failure ;
    /* start outer loop, break out if success or failure occurs */
    while(1)
    {
        t = gets_argmaxw (w, P, n) ; /* calculate where max(w) attained on the passive set */
	    success = ( t < 0 || w[t] < tol ) ;	/* reached termination, solution found, success */
	    failure = (iter >= itmax) ;        	/* exceeded iteration count, failure */

	    if (success || failure)
        {
            FREE_WORK ;
            
	        if (success)
            {
               cs_sprealloc (x,0) ; /* reallocates to actual size of x */
               return x ;
	        }
	        else
	        {
	    	   cs_spfree (x) ;
		       return (NULL) ;
	        }
        }
        
        
        if( s+1 >= smax ) /* not enough space allocated for x, xscale, Csub, beta */
        {
            smax = 2*smax ; /* reallocate memory after doubling smax */
            csi okx, okxs, okC, okbeta ;
            Csub = cs_realloc (Csub, (m+1)*smax, sizeof (double), &okC) ;
            beta = cs_realloc (beta, smax, sizeof (double), &okbeta) ;
            okx = cs_sprealloc (x, smax) ;
            okxs = cs_sprealloc (xscale, smax) ;
            
            if(!okx || !okxs || !okC ||!okbeta )   /* alloc failed, free everything and return NULL */
            {
                FREE_ALL ;
                return (NULL) ;
            }
             
            xp = x->p ; xscalep = xscale->p ;
            xi = x->i ; xscalei = xscale->i ;
            xx = x->x ; xscalex = xscale->x ;
        }
        
        /* adding a new index t */
        xx[s] = 0 ; xi[s] = t ; xp[1] = s+1 ; P[t] = 1 ;
        gets_qrupdate_reg (Csub, b, beta, s, A, diag, t, m, lambda) ;
        s++ ; /* sparsity level increases by 1 */
        
        while(1)
        {   iter++ ;
            /* set xls = b to pass it in for least squares */
            for (i = 0 ; i < s ; i++) /* need only the first s elements of b for the least squares solution */
            {
                xls[i] = b[i] ;
                
            }
            gets_uppersolve (Csub, m+1, s, xls) ; /* least squares solution written in xls */
            
            alpha = 2 ;
            for(p = 0; p < s; p++)
            {
                if(xls[p] <= 0)           /* computes alpha as min ratio over negative indices of xls */
                {
                    val = xx[p]/(xx[p] - xls[p]) ;
                    if(val < alpha) alpha = val ;
                }
            }
            
           
            if(alpha == 2) break ; /* no need for 'inner loop', xls is all postive, otherwise alpha will be less than 1 */
            
            /* inner loop, alpha < 1 */
            
            for(p = 0 ; p < s ; p++)     /* x = x + alpha*(xls -x) */
            {
                xx[p] += alpha*(xls[p] - xx[p]) ;
            }
            
            csi snew = 0 ;
            for(p = 0 ; p < s ; p++)
            {
                if(xx[p] >= tol)       /* drop zeros, taking in only values bigger than tol */
                {
                    xx[snew] = xx[p] ;
                    xi[snew] = xi[p] ;
                    snew++ ;
                }
                else
                {
                    P[xi[p]] = 0 ;      /* remove the smaller values */
                }
                
            }
            s = snew ;
            xp[1] = s ;
            
            for(i = 0 ; i < m ; i++)   /* need b = [lambda*d; 0] on entry to gets_qrfact_reg for qr factorization from scratch */
            {
                b[i] = lambda*d[i] ;
                
            }
            b[m] = 0 ;
            
            gets_qrfact_reg (Csub, b, beta, s, A, diag, m, x, lambda) ;
           
        } /* end of inner loop */
        
        xscalep[1] = s ;
        sumx = 0 ;
        for(p = 0 ; p < s ; p++)  /* sets x = xls and calculates the scaled x for matvec */
        {
            xx[p] = xls[p] ;
            sumx += xx[p] ; /* sum(x) for calculating w with regularization */
            xscalex[p] = xx[p]/diag[xi[p]] ;
            xscalei[p] = xi[p] ;
        }
        
        for(i = 0 ; i < m ; i++)   /* sets resid = d  for matvec */
        {
            resid[i] = d[i] ;
        }
        
        gets_matvec (A, xscale, resid, m) ;  /* resid = d - C*x = d - A*xscale */
        
        gets_treemult (D, resid, w) ; /* w = A'*resid */
        
        for(i = 0 ; i < n ; i++)    /* scaling after treemult and incorporate regularization: compute w = lambda^2 (C'resid) - sumx*ones(n,1) */
        {
            w[i] /= diag[i] ; /* w = C'resid */
            w[i] *= lambda * lambda ; /* w = lambda^2 (C'resid) */
            w[i] -= sumx ; /* w = lambda^2 (C'resid) - sumx*ones(n,1) */
        }

      /* end of outer loop, loops back up to compute argmax(w) */
        
    }
    
}



