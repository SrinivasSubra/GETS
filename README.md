# GETS
GETS: a Genomic Tree based Sparse solver. 

Written by Srinivas Subramanian and Tim Davis.

Refer to the article "A genomic tree based sparse solver" 
by Timothy A. Davis and Srinivas Subramanian (see GETS_article.pdf in this directory).

Nonnegative sparse recovery is performed for a genomics problem which is concerned with the reconstruction of concentrations of bacterial species from an environmental sample.

Nonnegative least squares (NNLS) or Nonnegative regularization (NNREG) optimization problems solved via the GETS solver, an efficient implementation of the Lawson Hanson algorithm. 

  Given a genomic dataset (k-mer matrix of DNA sequences), the inherent structure of the genomic problem is exploited to uncover an evolutionary family tree type relationship between the species. This genomic tree enables a sparse representation of the problem which is created in the offline stage of GETS, a one time computation. This allows for reduced storage and asymptotic speed ups via sparse matrix computations, whenever the solver is used. 
  
GETS is primarily written in C, with an interface for use in MATLAB through its MEX functions. 

GETS uses CSparse, a concise sparse matrix package by Tim Davis. 
This package (CSparse v4.0.0) is already included in the GETS/MATLAB directory and does not need to be separately installed. 

Note: This repository uses Git Large File Storage (Git LFS) since the size of the Data directory is about 500MB. A repository with LFS data can be cloned (i.e., with the usual git clone command), but the 'Download ZIP' button on the GitHub web interface doesn't include the large files, only the pointers. A complete zipped version of GETS which includes the large files can be directly downloaded via this link: https://drive.google.com/file/d/1U-uuCk20DGlMJ3A-YhubMYTMZ9-Eo1DL/view?usp=share_link. 

***********************************************************************************

# Installation for use in MATLAB

To compile and install GETS for use in MATLAB (along with CSparse),

1) Go to the GETS/MATLAB directory

2) Type "gets_install" in the MATLAB Command Window or equivalently Run "gets_install.m" 

The installation takes about a minute and you will see the "CSparse successfully compiled" and 
"GETS successfully compiled" messages displayed. 

***********************************************************************************

# Run the MATLAB scripts to test GETS or to reproduce the results in the article 

1) First install GETS for use in MATLAB by following the steps shown above 
2) Go to the GETS/MATLAB/Tests directory 
3) Run the MATLAB scripts "NNREG_Tests_small.m" for the tests on the small dataset 
4) Run the MATLAB scripts "NNREG_Tests_large.m" for the tests on the large dataset 

The tests compare the performance of GETS with MATLAB's lsqnonneg.
You can display the default saved tests results, including the histogram plots, without running the actual tests, by running only the bottom section "Display test results" of the MATLAB scripts. 

To run a single test for a specific right hand side, run the "NNREG_Singletest_small.m" or "NNREG_Singletest_Large.m"

To run tests for NNLS instead of NNREG, just follow the above steps with NNLS in the place of NNREG. 

To perform the offline computations that create the treedata struct, run "Offline.m" 

*************************************************************************************

# Help for GETS

In the MATLAB command window type: "help GETS" or "help gets_nnreg", "help gets_nnls", "help gets_offline" to get the MATLAB style help descriptions for using these functions along with examples. 
For questions or comments contact Srinivas Subramanian (email:srini2092@tamu.edu).
