#include "gets_mex.h"
/* Reverse Brain Transplant */
/* Transfer contents of x to a mxArray without copying  */
/**/
mxArray *rbt (void *x, int dim1, int dim2 , mxClassID class) /* x is dim1-by-dim2 of type class*/
{
    mxArray *mex_f ;
    mwSize dims[2] ;
    dims[0] = 0 ; dims[1] = 0 ;
    mex_f = mxCreateNumericArray(2, dims, class, mxREAL) ;
    mxSetM(mex_f, (mwSize) dim1) ;
    mxSetN(mex_f, (mwSize) dim2) ;
    mxFree(mxGetData(mex_f)) ;
    mxSetData(mex_f, x) ;
    // mexMakeMemoryPersistent(x) ;
    return mex_f ;
}

