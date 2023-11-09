GETS/MATLAB directory which contains the MATLAB mexFunction interfaces for GETS, the CSparse package, 
and the Tests folder which contains MATLAB test scripts. 

****** INSTALLATION FOR USE IN MATLAB *********************************************

To compile and install GETS for use in MATLAB (along with CSparse),

While in this directory, type "gets_install" in the MATLAB Command Window or equivalently Run "gets_install.m" 

The installation takes about a minute and you will see the "CSparse successfully compiled" and 
"GETS successfully compiled" messages displayed. 

***********************************************************************************

**** RUN THE MATLAB SCRIPTS TO TEST GETS/REPRODUCE RESULTS IN THE ARTICLE ******

1) First install GETS for use in MATLAB 
2) Go to the Test directory 
3) Run the MATLAB scripts "NNREG_Tests_small.m" for the tests on the small dataset 
4) Run the MATLAB scripts "NNREG_Tests_large.m" for the tests on the large dataset 

The tests compare the performance of GETS with MATLAB's lsqnonneg.
You can display the default saved tests results, including the histogram plots, without running the actual tests by running only the bottom section "Display test results" of the MATLAB scripts. 

To run a single test for a specific right hand side, run the "NNREG_Singletest_small.m" or "NNREG_Singletest_Large.m"

To run tests for NNLS instead of NNREG, just follow the above steps with NNLS in the place of NNREG. 

To perform the offline computations that create the treedata struct, run "Offline.m" 

*************************************************************************************

****** HELP FOR GETS ****************************************************************

In the MATLAB command window type: "help GETS" or "help gets_nnreg", "help gets_nnls", "help gets_offline" to get the MATLAB style help descriptions for using these functions along with examples. 

 


