GETS/MATLAB/Test directory 

GETS needs to be installed first prior to running the tests. See README.txt in GETS/MATLAB 

**** RUN THE MATLAB SCRIPTS TO TEST GETS/REPRODUCE RESULTS IN THE ARTICLE ***********

 Run the MATLAB scripts "NNREG_Tests_small.m" for the tests on the small dataset 
 Run the MATLAB scripts "NNREG_Tests_large.m" for the tests on the large dataset 

The tests compare the performance of GETS with MATLAB's lsqnonneg.
You can display the default saved tests results, including the histogram plots, without running the actual tests by running only the bottom section "Display test results" of the MATLAB scripts. 

To run a single test for a specific right hand side, run the "NNREG_Singletest_small.m" or "NNREG_Singletest_Large.m"

To run tests for NNLS instead of NNREG, just follow the above steps with NNLS in the place of NNREG. 

To perform the offline computations that create the treedata struct, run "Offline.m" 

*************************************************************************************

****** HELP FOR GETS ****************************************************************

In the MATLAB command window type: "help GETS" or "help gets_nnreg", "help gets_nnls", "help gets_offline" to get the MATLAB style help descriptions for using these functions along with examples. 

 


