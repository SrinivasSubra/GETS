#include "cs.h"

/* treedata struct: efficient representation of genomic data enabling fast computation of A'*r in gets_treemult */
/* mainly stores the sparse form for Diff matrix separated into +1,-1 and non-binary entries. Also stores the post ordering, reordered parent, reordered matrix A and the normalization factors that normalize the reordered matrix A */

typedef struct gets_treedata_struct
{
    csi m;         /* number of rows */
    csi n;         /* number of columns */
    csi *bposp;    /* column pointers for binary +1 entries of Diff */
    csi *bnegp;    /* column pointers for binary -1 entries of Diff  */
    short *bposi;  /* row indices for binary +1 entries of Diff  */
    short *bnegi;  /* row indices for binary -1 entries of Diff  */
    csi *xp;       /* column pointers for non binary entries of Diff  */
    short *xi;     /* row indices for non binary entries of Diff  */
    char *xx;      /* numerical values for non binary entries of Diff */
    char *A;       /* reordered unnormalized integer matrix A */
    csi *diag;     /* normalization factors: column sums of reordered A */
    csi *ipt;      /* parent array in the reordered tree, ipt = invpost(parent(post))) */
    csi *post;     /* post ordering of the MST */
} treedata ;
 

/* --- GETS functions ------------------------- */

void gets_applyhouse (const double *C, csi j, csi m, double beta, double *x) ;
void gets_makehouse (double *x, double *beta, csi n) ;
void gets_uppersolve (const double *C, csi m, csi s, double *x) ;
void gets_qrfact (double *C, double *b, double *beta, csi s, const char *A, const csi *diag, csi m, cs *x) ;
void gets_qrupdate (double *C, double *b, double *beta, csi s, const char *A, const csi *diag, csi j, csi m) ;
treedata *gets_offline (const char *A, csi m, csi n) ;
csi *gets_prim (const char *A, csi m, csi n) ;
cs *gets_nnls (const treedata *D, const double *d ) ;
csi gets_argmaxw (double *w, char *P, csi n ) ;
void gets_treemult (const treedata *D, const double *b, double *w) ;
void gets_matvec (const char *A, const cs *x, double *w, csi m ) ;

      /* --- NNREG specific functions ---*/

void gets_qrfact_reg (double *C, double *b, double *beta, csi s, const char *A, const csi *diag, csi m, cs *x, double lambda) ;
void gets_qrupdate_reg (double *C, double *b, double *beta, csi s, const char *A, const csi *diag, csi j, csi m, double lambda) ;
cs *gets_nnreg (const treedata *D, const double *d, double lambda) ;

/* ----------------------------------------------*/
