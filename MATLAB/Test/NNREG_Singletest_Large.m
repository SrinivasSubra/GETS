% NNREG_Singletest_Large.m
% Compares the performance of GETS solver gets_nnreg and MATLAB's lsqnonneg 
% on the NNREG problem built with large data (matrix of size 4096x188326) 
% and a specified right hand side y. 

load('../../Data/Large_input.mat') ; % load Large input data 
i = 201 ; % i can be any integer between 1 to 216 except for [72,79,90,107,111]
y = load(sprintf('../../Data/Y/profile%d-countsN6.txt',i)) ; % load y_i data 
y = y/sum(y) ; % normalize y 
C_large = double(D_large.A).*(1./double(sum(D_large.A))) ; % normalize to get C from A 

lambda = 10000 ; 
ytil = [lambda*y ; 0] ;
[~,N] = size(C_large) ; 
Ctil = [lambda*C_large ; ones(1,N)] ; % Ctilde matrix 

tic ; x2 = gets_nnreg(D_large,y,lambda) ;     
tC = toc ; % GETS time 
fprintf ('GETS time: %g\n', tC) ;

tic ; x1 = lsqnonneg(Ctil,ytil) ; 
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
