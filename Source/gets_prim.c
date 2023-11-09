#include "gets.h"
/* compute a minimum spanning tree (MST) of the complete graph associated with the Delta matrix using Prim's algorithm. Delta(i,j) = nnz(A(:,i)-A(:,j)). Delta, a large matrix, is not stored but computed implicitly on the fly.
    Input: matrix A, Output: the parent array of MST */

#define FREE_WORK \
{                               \
    cs_free (key) ;          \
    cs_free (intree) ;         \
}

#define FREE_ALL \
{                               \
    FREE_WORK ;                 \
    cs_free(parent) ;          \
                 \
}

csi *gets_prim (const char*A, csi m, csi n)
{
    csi i, j, k, t, *parent, min, *key = NULL ;
    char *intree = NULL ; /* initialize workspace variables as NULL */
    
    key = cs_malloc(n, sizeof(csi)) ;
    parent = cs_malloc(n, sizeof(csi)) ;
    intree = cs_calloc(n, sizeof(char)) ; /* Set intree as all zeros */
    /* During the algorithm, intree[j] = 1 iff j is a vertex in the current tree. For vertices i not in the tree, parent[i] is the vertex in the current tree that is closest to i. That is, parent[i]->i is that edge with weight key[i], where key[i] is the minimum weight of any edge connecting i to a vertex in the current tree. Each time a vertex is added to the current tree, parent and key values of non-tree vertices are updated if required. At the end of the algorithm, parent is the parent array of the MST with edge weights stored in key */
    if(!key || !parent || !intree){ FREE_ALL ; return(NULL) ; }
    /* alloc failed, free everything and return NULL */
    
    key[0] = 0 ;
    parent[0] = -1 ;
    /* let 0 be the root of the tree. intree[0] = 1 happens when k = 0 in loop */
    
    for(i = 1 ; i < n ; i++)
    {
        key[i] = m + 2 ;   /* a value bigger than m to use in place of INFINITY since the edge weights will all be <= m  */
    }
    
    /* Prims */
    for(k = 0 ; k < n ; k++)
    {
        /* EXTRACT-MIN of the non-tree vertices */
        min = m + 4 ;   /* bigger than all the key values */
        for(i = 0 ; i < n ; i++)
        {
            if(intree[i]==0)   /* there has to be a non-intree node as long as k < n, since intree grows by 1 during each iteration of k */
            {
                if(min > key[i])   /* key is non-negative */
                {
                    min = key[i] ;
                    t = i ;
                }
            }
        }
        
        intree[t] = 1 ; /* add extracted vertex to the tree */
        
        /* loop over non-tree elements to update key and parent */
        for(i = 0 ; i < n ; i++)
        {
            if(intree[i]==0)
            {
                
                csi wti = 0 ;   /* wti is weight of edge between t and i, to be computed if i is not in-tree */
                /* wti = nnz(A(:,t) - A(:,i)) is computed implicitly */
                for(j = 0 ; j < m ; j++)
                {
                    if(A[i*m +j]!=A[t*m + j])
                    {
                        wti++ ;
                    }
                }
                
                /* update the key and parent values at i if needed */
                if((key[i] > wti))
                {
                    key[i] = wti ;
                    parent[i] = t ;
                    
                }
                
                
            }
        }
        
        
    }
    
    FREE_WORK ;
    return (parent) ;
        
}
