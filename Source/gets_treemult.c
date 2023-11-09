#include "gets.h"
/* compute the residual w = A'*b by using the genomic tree data.
 D is the struct that encapsulates the compact representation for the problem.
 Since Diff(:,j) = A(:,j) - A(:,k), the genomic tree gives us
    w(j) = w(k) + Diff(:,j)'*b , where k = ipt(j), k is the parent of j in the reordered tree */
void gets_treemult (const treedata *D, const double *b, double *w)
{    
    csi p, j, n ;
    const csi *Dbposp, *Dbnegp, *Dxp, *Dipt ;
    const short *Dbposi, *Dbnegi, *Dxi ;
    const char *Dxx ;
						     /* check inputs */
    n = D->n ; Dbposp = D->bposp ; Dbnegp = D->bnegp ; Dxp = D->xp ; Dipt = D->ipt ;
    Dbposi = D->bposi ;  Dbnegi = D->bnegi ; Dxi = D->xi ;
    Dxx = D->xx ;
     
/* w = Diff'*b is first computed and then the parent values for each w(i) are added later. Diff = Dbpos + Dbneg + Dx, where Dbpos and Dneg are sparse binary +1 and -1 matrices respectively. Dx is a sparse matrix with non-binary values.
   So w = Dbpos'*b + Dbneg'*b + Dx'*b.
   The computation is split into 3 separate loops rather than a single loop, since this method is found to be the fastest empirically */
    
    for(j = 0 ; j < n ; j++)    /* Dx'*b */
    { 
      double wj = 0 ; 
    
	  for (p = Dxp [j] ; p < Dxp [j+1] ; p++) /* Dx(:,j)'*b */
	  {
	    wj += Dxx [p] * b [Dxi[p]] ; /*sum of the non-zero terms in dot product */
	  }
      
      w[j] = wj ;
      
    }
	
    for(j = 0 ; j < n ; j++)   /* Dbpos'*b */
    {    
      double wj = w[j] ;
      
      for (p = Dbposp [j] ; p < Dbposp [j+1] ; p++) /* Dbpos(:,j)'*b */
	  {   
	    wj += b [Dbposi [p]] ; /*sum of the non-zero terms in dot product is just addition due to non-zeros being +1s */
	  }
      
      w[j] = wj ;
    }

    for(j = 0 ; j < n ; j++)  /* Dbneg'*b */
    {
      double wj = w[j] ;
      
	  for (p = Dbnegp [j] ; p < Dbnegp [j+1] ; p++) /* Dbneg(:,j)'*b */
	  {   
	    wj -= b [Dbnegi [p]] ; /*sum of the non-zero terms in dot product is just subtraction due to non-zeros being -1s */
	  } 
      
      w[j] = wj ;
    }
    
    /* parent values added to each child. Tree nodes being topologically sorted in reverse post order ensures that parent values are updated before children */
    for(j = 1 ; j < n ; j++)
    {
      w[j] += w[Dipt[j]] ;
        
    } 
    
}

