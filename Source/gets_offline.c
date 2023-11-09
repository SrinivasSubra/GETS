#include "gets.h"
/* offline routine to create the treedata struct for efficient representation of the genomic data. This enables fast computation of A'*r in gets_treemult (struct definition is in gets.h). Compute and store the minimum spanning tree, post ordering of the tree vertices, reordered matrix A and column sums for diag, parent array in the reordered tree and the sparse components for the Diff matrix. Diff = Dbpos + Dbneg + Dx, where Dbpos and Dneg are sparse binary +1 and -1 matrices respectively. Dx is a sparse matrix with non-binary values.
  Input: matrix A, m, n  Output: treedata struct D
*/
 
#define FREE_WORK \
{                               \
    cs_free (parent) ;          \
    cs_free (invpost) ;         \
}

#define FREE_ALL \
{                               \
    FREE_WORK ;                 \
    freetreedata (&D) ;          \
                 \
}

void freetreedata (treedata **D_handle)
{
    if (D_handle == NULL) return ;
    treedata *D = *D_handle ;
    if (D == NULL) return ;
    cs_free (D->bposp) ;
    cs_free (D->bnegp) ;
    cs_free (D->bposi) ;
    cs_free (D->bnegi) ;
    cs_free (D->xp) ;
    cs_free (D->xi) ;
    cs_free (D->xx) ;
    cs_free (D->A) ;
    cs_free (D->diag) ;
    cs_free (D->ipt) ;
    cs_free (D->post) ;
    cs_free (D) ;
    (*D_handle) = NULL ;  /*the struct itself is set as NULL, indicates the contents are NULL*/
}

treedata *gets_offline(const char *A, csi m, csi n)
{
    /* workspace variables that need to be freed later in FREE_WORK are initialized here as NULL */
    csi i, j, k, t, *parent = NULL, *invpost = NULL, *post, *diag, *ipt ;
    treedata *D = cs_calloc (1,sizeof(treedata)) ;
    if(!D) { FREE_ALL ; return (NULL) ; }
    
    D->m = m ;
    D->n = n ;
    D->A = cs_malloc (m*n, sizeof(char)) ;
    D->diag = cs_malloc (n, sizeof(csi)) ;
    D->ipt = cs_malloc (n, sizeof(csi)) ;
    if(!(D->A)||!(D->diag)||!(D->ipt))
    { FREE_ALL ; return (NULL) ; }
    
    char *Ar ;
    Ar = D->A ;
    diag = D->diag ;
    ipt = D->ipt ;
    parent = gets_prim (A, m, n) ; /* Find the MST using Prim's Algorithm */
    if(!parent) { FREE_ALL ; return(NULL) ; }
    
    D->post = cs_post (parent, n) ; /* Post ordering the MST by DFS */
    if(!(D->post)) { FREE_ALL ; return(NULL) ; }
    post = D->post ;
    
    csi temp, start, end ;
     /* Reversing post to make the root node 0 as first element in array. Reverse post ordering of a tree is topologically sorted, i.e, a parent node always occurs before a child */
    start = 0 ; end = n-1 ;
    while(start < end)
    {
        temp = post[start] ;
        post[start] = post[end] ;
        post[end] = temp ;
        start++ ; end-- ;
    }
    
    /* Reordering the matrix, Ar = A(:,post) and diag is column sums of Ar. Ar[:,i] = A[:,post[i]] */
    for( i = 0 ; i < n ; i++)
    {
        t = post[i] ;
        csi colsum = 0 ;
        for(j = 0 ; j < m ; j++)
        {   temp = A[t*m + j] ;
            Ar[i*m + j] = temp ;
            colsum = colsum + temp ;
        }
        diag[i] = colsum ;
        
    }
    
    invpost = cs_malloc (n, sizeof(csi)) ;
    if(!invpost) { FREE_ALL ; return(NULL) ; } ;
    /* Compute the inverse of post */
    for(i = 0 ; i < n ; i++)
    {
        invpost[post[i]] = i ;
        
    }
    /* ipt is the parent array in the reordered tree. ipt = invpost(parent(post))) */
    ipt[0] = -1 ;  /* root has no parent */
    
    for(i = 1 ; i < n ; i++)
    {   k = post[i] ;
        j = parent[k] ;
        ipt[i] = invpost[j] ;
    }
    
    csi nbpos, nbneg, nbx , Diffji ;
    nbpos = 0 ; nbneg = 0 ; nbx = 0 ;
    
    /* Traversing to count the total number of binary postive, negative and non-binary x values for allocating memory. Diff(:,i) = A(:,i) - A(:,ipt(i)) */
   
    for( i = 0 ; i < n ; i++)
    {
        t = ipt[i] ;
        for( j = 0 ; j < m ; j++)
        {
            if(t==-1)    /* when i is 0, ipt[0] = -1 */
            {
               Diffji = Ar[j] ;
            }
            else
            {
               Diffji = Ar[i*m + j] - Ar[t*m + j] ;
            }
            if(Diffji!=0)
            {
                if(Diffji==1)
                {
                    nbpos++ ;
                }
                else if(Diffji==-1)
                {
                    nbneg++ ;
                }
                else
                {
                    nbx++ ;
                }
                
            }
            
        }
    }
    
   csi *Dbposp, *Dbnegp, *Dxp ;
   short *Dbposi, *Dbnegi, *Dxi ;
   char *Dxx ;
    
    D->bposp = cs_malloc (n+1, sizeof(csi)) ;
    D->bnegp = cs_malloc (n+1, sizeof(csi)) ;
    D->xp = cs_malloc (n+1,sizeof(csi)) ;
    D->bposi = cs_malloc (nbpos, sizeof(short)) ;
    D->bnegi = cs_malloc (nbneg, sizeof(short)) ;
    D->xi = cs_malloc (nbx, sizeof(short)) ;
    D->xx = cs_malloc (nbx, sizeof(char)) ;
    
    if(!(D->bposp)||!(D->bnegp)||!(D->xp)||!(D->bposi)||!(D->bnegi)||!(D->xi)||!(D->xx)) { FREE_ALL ; return (NULL) ; }
    
    Dbposp = D->bposp ; Dbnegp = D->bnegp ; Dxp = D->xp ;
    Dbposi = D->bposi ;  Dbnegi = D->bnegi ; Dxi = D->xi ;
    Dxx = D->xx ;
    Dbposp[0]= 0 ; Dbnegp[0] = 0; Dxp[0] = 0 ;
    
    nbpos = 0 ; nbneg = 0 ; nbx = 0 ;
    
    /* Computing the entries of Diff */
    for( i = 0 ; i < n ; i++)
    {
        t = ipt[i] ;
        for( j = 0 ; j < m ; j++)
        {
            if(t==-1)    /* when i is 0, ipt[0] = -1 */
            {
                Diffji = Ar[j] ;
            }
            else
            {
                Diffji = Ar[i*m + j] - Ar[t*m + j] ;
            }
           
            if(Diffji!=0)
            {
                if(Diffji==1)
                {
                    Dbposi[nbpos] = j ;
                    nbpos++ ;
                }
                else if(Diffji==-1)
                {
                    Dbnegi[nbneg] = j ;
                    nbneg ++ ;
                }
                else
                {
                    Dxi[nbx] = j ;
                    Dxx[nbx] = Diffji ;
                    nbx++ ;
                }
                
            }
            
        }
        Dbposp[i+1] = nbpos ;
        Dbnegp[i+1] = nbneg ;
        Dxp[i+1] = nbx ;
        
    }

    FREE_WORK ;
    return D ;
    
}


