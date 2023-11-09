% NNLS_Singletest_small.m
% Compares the performance of GETS solver gets_nnls and MATLAB's lsqnonneg 
% on the NNLS problem with small data (matrix of size 4096x10046) 
% and a specified right hand side y. 

load('../../Data/small_input.mat') ; % load small input data 
i = 42 ; % i can be any integer between 1 to 216 except for [72,79,90,107,111]
y = load(sprintf('../../Data/Y/profile%d-countsN6.txt',i)) ; % load y_i data 
y = y/sum(y) ; % normalize y 
C_small = double(D_small.A).*(1./double(sum(D_small.A))) ; % normalize to get C from A 

tic ; x2 = gets_nnls(D_small,y) ;  
tC = toc ; % GETS time 
fprintf ('GETS time: %g\n', tC) ;

tic ; x1 = lsqnonneg(C_small,y) ; 
tM = toc ; % MATLAB's lsqnonneg time 
fprintf ('MATLAB lsqnonneg time: %g\n', tM) ;
% display the results 
fprintf ('speed up ratio: %g\n', tM/tC) ;

fprintf ('x difference: %g\n', norm(x1-x2)) ;

I1 = find(x1) ;
I2 = find(x2) ;
s1 = length(setdiff(I1,I2)) ;
s2 = length(setdiff(I2,I1)) ;
fprintf ('size of support symmetric set difference: %d \n', s1+s2) ;
fprintf ('solution sparsity: %d \n', nnz(x2)) ;


