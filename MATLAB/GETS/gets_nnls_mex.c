#include "gets_mex.h"
#include "cs_mex.h"

/* MEX function for gets_nnls. Receives the input struct D and right hand side vector d from MATLAB. See the GETS/MATLAB/Test folder. */

void mexFunction
(
 int nargout,
 mxArray *pargout [ ],
 int nargin,
 const mxArray *pargin [ ]
 )

{
    mxArray *field;
    const mxArray *in_struct ;
    treedata s_struct, *s ;
    double *d ;
    csi m, n ;
    
    if (nargout > 1 || nargin != 2)
    {
        mexErrMsgTxt ("Usage:  x = gets_nnls (D, d)") ;
    }
    /*------------------------------------------------------------*/
    /* get the input struct (brain transplant) */
    /*------------------------------------------------------------*/
    
    s = &s_struct ; /* no need to malloc this */
    s->m = 0 ;
    s->n = 0 ;
    s->bposp = (csi *) NULL ;
    s->bnegp = (csi *) NULL ;
    s->bposi = (short *) NULL ;
    s->bnegi = (short *) NULL ;
    s->xp = (csi *) NULL ;
    s->xi = (short *) NULL ;
    s->xx = (char *) NULL ;
    s->A = (char *) NULL ;
    s->diag = (csi *) NULL ;
    s->ipt = (csi *) NULL ;
    s->post = (csi *) NULL ;
    
    in_struct = pargin [0] ;
    if (!mxIsStruct (in_struct)) mexErrMsgTxt ("input must be a struct") ;
    
    if ((field = mxGetField (in_struct, 0, "m")) != NULL)
    {
        s->m = (csi) mxGetScalar (field) ;
    }
    
    if ((field = mxGetField (in_struct, 0, "n")) != NULL)
    {
        s->n = (csi) mxGetScalar (field) ;
    }
                                                    
    m = s->m ;
    n = s->n ;
    
    if ((field = mxGetField (in_struct, 0, "bposp")) != NULL)
    {
        if (mxGetClassID (field) != mxINT64_CLASS)
        {
            mexErrMsgTxt ("bposp wrong type") ;
        }
        if (mxGetNumberOfElements (field) != (s->n +1) )
        {
            mexErrMsgTxt ("bposp wrong size") ;
        }
        s->bposp = (csi *) mxGetData (field) ;
    }
    
    
    if ((field = mxGetField (in_struct, 0, "bnegp")) != NULL)
    {
        if (mxGetClassID (field) != mxINT64_CLASS)
        {
            mexErrMsgTxt ("bnegp wrong type") ;
        }
        if (mxGetNumberOfElements (field) != (s->n +1) )
        {
            mexErrMsgTxt ("bnegp wrong size") ;
        }
        s->bnegp = (csi *) mxGetData (field) ;
        
    }
    
    
    if ((field = mxGetField (in_struct, 0, "bposi")) != NULL)
    {
        if (mxGetClassID (field) != mxINT16_CLASS)
        {
            mexErrMsgTxt ("bposi wrong type") ;
        }
        if (mxGetNumberOfElements (field) != s->bposp[s->n] )
        {  
            mexErrMsgTxt ("bposi wrong size") ;
        }
       
        s->bposi = (short *) mxGetData (field) ;
    }
    
    if ((field = mxGetField (in_struct, 0, "bnegi")) != NULL)
    {
        if (mxGetClassID (field) != mxINT16_CLASS)
        {
            mexErrMsgTxt ("bnegi wrong type") ;
        }
        
        if (mxGetNumberOfElements (field) != s->bnegp[s->n] )
        {
            mexErrMsgTxt ("bnegi wrong size") ;
        }
        
        s->bnegi = (short *) mxGetData (field) ;
    }
    
    if ((field = mxGetField (in_struct, 0, "xp")) != NULL)
    {
        if (mxGetClassID (field) != mxINT64_CLASS)
        {
            mexErrMsgTxt ("xp wrong type") ;
        }
        if (mxGetNumberOfElements (field) != (s->n +1) )
        {
            mexErrMsgTxt ("xp wrong size") ;
        }
        s->xp = (csi *) mxGetData (field) ;
    }
    
    if ((field = mxGetField (in_struct, 0, "xi")) != NULL)
    {
        if (mxGetClassID (field) != mxINT16_CLASS)
        {
            mexErrMsgTxt ("xi wrong type") ;
        }
        if (mxGetNumberOfElements (field) != s->xp[s->n] )
        {    
            mexErrMsgTxt ("xi wrong size") ;
        }
        s->xi = (short *) mxGetData (field) ;
    }
    
    
   if ((field = mxGetField (in_struct, 0, "xx")) != NULL)
    {
        if (mxGetClassID (field) != mxINT8_CLASS)
        {
            mexErrMsgTxt ("xx wrong type") ;
        }
        if (mxGetNumberOfElements (field) != s->xp[s->n])
        {
            mexErrMsgTxt ("xx wrong size") ;
        } 
        s->xx = (char *) mxGetData (field) ;
    }
    
    if ((field = mxGetField (in_struct, 0, "A")) != NULL)   /*Assumes A is char */
    {
        if (mxGetClassID (field) != mxINT8_CLASS)
        {
            mexErrMsgTxt ("A wrong type") ;
        }
        if (mxGetNumberOfElements (field) != (s->m)*(s->n))
        {
            mexErrMsgTxt ("A wrong size") ;
        }
        s->A = (char *) mxGetData (field) ;
    }
    
    if ((field = mxGetField (in_struct, 0, "diag")) != NULL)
    {
        if (mxGetClassID (field) != mxINT64_CLASS)
        {
            mexErrMsgTxt ("diag wrong type") ;
        }
        if (mxGetNumberOfElements (field) != s->n)
        {
            mexErrMsgTxt ("diag wrong size") ;
        }
        s->diag = (csi *) mxGetData (field) ;
    }
    
    if ((field = mxGetField (in_struct, 0, "ipt")) != NULL)
    {
        if (mxGetClassID (field) != mxINT64_CLASS)
        {
            mexErrMsgTxt ("ipt wrong type") ;
        }
        if (mxGetNumberOfElements (field) != s->n)
        {
            mexErrMsgTxt ("ipt wrong size") ;
        }
        s->ipt = (csi *) mxGetData (field) ;
    }
    
    if ((field = mxGetField (in_struct, 0, "post")) != NULL)
    {
        if (mxGetClassID (field) != mxINT64_CLASS)
        {
            mexErrMsgTxt ("post wrong type") ;
        }
        if (mxGetNumberOfElements (field) != s->n)
        {
            mexErrMsgTxt ("post wrong size") ;
        }
        s->post = (csi *) mxGetData (field) ;
    }
    
    if( mxGetM(pargin[1]) != m)
    {
        mexErrMsgTxt ("d wrong size, needs to be a column vector of size m ") ;
               
    }
    d = (double *) mxGetData (pargin [1]) ;
    cs *x, *temp ;
    
    x = gets_nnls (s, d) ;
    if (!x) {mexErrMsgTxt ("failure: iteration count exceeded or out of memory") ;}
     /* x can be NULL due to iteration count being exceeded or due to failure of memory allocation */
    temp = cs_transpose (x, 1) ;    /* sort indices using double transpose */
    cs_spfree (x) ;
    x = cs_transpose (temp, 1) ;
    cs_spfree (temp) ;
    pargout [0] = cs_mex_put_sparse (&x) ;
    
}

