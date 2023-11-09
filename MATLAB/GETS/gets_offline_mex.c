#include "gets_mex.h"
#include "cs_mex.h"

/* MEX function for gets_offline. Receives the input matrix A from MATLAB. See Offline.m in the GETS/MATLAB/Test folder. */

void mexFunction
(
 int nargout,
 mxArray *pargout [ ],
 int nargin,
 const mxArray *pargin [ ]
 )
{
    
    csi m, n ;
    treedata *D ;
    char *A;
    
    if (nargout > 1 || nargin != 1)
    {
        mexErrMsgTxt ("Usage: D = gets_offline (A)") ;
    }
    
    A = (char*) mxGetData(pargin[0]) ;   /* input dense matrix A in int8 */
    m = mxGetM (pargin[0]) ;   /* get number of rows and columns of A */
    n = mxGetN (pargin[0]) ;
    
    D = gets_offline (A, m, n) ;
    
    /*-----------------------------------------------------------*/
    /* output a MATLAB struct (reverse brain transplant) */
    /*-----------------------------------------------------------*/
    static const char *fnames [ ]  = { "m",
                                       "n",
                                       "bposp",
                                       "bnegp",
                                       "bposi",
                                       "bnegi",
                                       "xp",
                                       "xi",
                                       "xx",
                                       "A",
                                       "diag",
                                       "ipt",
                                       "post" } ;
    
    pargout[0] = mxCreateStructMatrix(1,1,13,fnames) ;
    
    mxArray *mex_m, *mex_n,
            *mex_bposp, *mex_bnegp, *mex_xp,
            *mex_bposi, *mex_bnegi, *mex_xi,
            *mex_xx, *mex_A,
            *mex_diag, *mex_ipt, *mex_post ;
    
    mex_m = mxCreateDoubleScalar(m) ;
    mxSetFieldByNumber(pargout[0], 0, 0, mex_m) ;
    
    mex_n = mxCreateDoubleScalar(n) ;
    mxSetFieldByNumber(pargout[0], 0, 1, mex_n) ;
    
    mex_bposp = rbt(D->bposp, 1, n+1, mxINT64_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 2, mex_bposp) ;
    
    mex_bnegp = rbt(D->bnegp, 1, n+1, mxINT64_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 3, mex_bnegp) ;
    
    mex_bposi = rbt(D->bposi, 1, D->bposp[n], mxINT16_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 4, mex_bposi) ;
    
    mex_bnegi = rbt(D->bnegi, 1, D->bnegp[n], mxINT16_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 5, mex_bnegi) ;
    
    mex_xp = rbt(D->xp, 1, n+1, mxINT64_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 6, mex_xp) ;
    
    mex_xi = rbt(D->xi, 1, D->xp[n], mxINT16_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 7, mex_xi) ;
    
    mex_xx = rbt(D->xx, 1, D->xp[n], mxINT8_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 8, mex_xx) ;
    
    mex_A = rbt(D->A, m, n, mxINT8_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 9, mex_A) ;
    
    mex_diag = rbt(D->diag, 1, n, mxINT64_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 10, mex_diag) ;
    
    mex_ipt = rbt(D->ipt, 1, n, mxINT64_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 11, mex_ipt) ;
    
    mex_post = rbt(D->post, 1, n, mxINT64_CLASS) ;
    mxSetFieldByNumber(pargout[0], 0, 12, mex_post) ;
    

    
}

