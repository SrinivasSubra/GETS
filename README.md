# GETS
GETS: a Genomic Tree based Sparse solver. 
By Dr. Timothy A. Davis and Srinivas Subramanian. 

Nonnegative sparse recovery for a metagenomics problem. 
Nonnegative least squares optimization problem is solved via the Lawson Hanson algorithm. 
GETS is a C based solver with a MATLAB mex function interface for the solver and offline stage  computations. 
Refer to the write up (to be included). 

{The main idea - discovering an evolutionary family tree type relationship between the columns of the k-mer matrix that allows for a sparse representation of the data giving us reduced storage and large asymptotic speed ups. The offline computations create a struct that encapsulates the compact representation of the problem. 
(See GETS/Source/gets_offline.c and GETS/MATLAB/Test/Offline.m)
This struct is utilized by the main solver to efficiently compute C’r and Cx. 
(See GETS/Source/gets_nnls.c)
C'r, the main bottleneck of the algorithm, is asymptotically sped up by exploiting the tree relationships. It becomes equivalent to a sparse matrix times dense vector problem. 
Further, QR updates are implemented to speed up the Lawson Hanson NNLS algorithm.}

GETS uses CSparse, a concise sparse matrix package by Dr. Timothy A. Davis. 
This package is already included in the GETS/MATLAB directory. 

In MATLAB, type "gets_install" while in the GETS/MATLAB directory to
compile and install GETS and CSparse for use in MATLAB. 

To perform the tests for the solver or the offline computations, run the MATLAB scripts in the 
GETS/MATLAB/Tests directory. The tests compare the performance of GETS with MATLAB's lsqnonneg.  

Acknowledgements to Dr. Simon Foucart for introducing this problem and to Dr. David Koslicki for providing the metagenomic data. 

--------------------------------------------------------------------------------
Contents:
--------------------------------------------------------------------------------
TO DO 
