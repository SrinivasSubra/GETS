function x = gets_nnreg (D, d)
%GETS_NNREG solve a genomic problem by non negative regularization (NNREG) via the Lawson Hanson algorithm. 
%
% x = gets_nnreg (D, d, lambda)
%
% Inputs: treedata struct D, right hand side vector d, and regularization parameter lambda.
% Output: sparse vector x, the solution to the problem.
%
%   NNREG: min (||v||_1)^2 + λ^2(||d − Cv||_2)^2 subject to v ≥ 0,
%
% where C is the k-mer frequency matrix with column sums equal to one. 
% C is the normalized form of the integer k-mer matrix A. 
% treedata struct D, created in the offline stage by gets_offline, 
% contains the sparse representation of the data allowing for reduced storage and
% large asymptotic speed ups. D is obtained by D = gets_offline (A) 
%
% Example:
%
% load('../../Data/small_input.mat') ; % load small input data 
% D_small = gets_offline (A) ;
% (normally, D_small would have been saved to a mat-file for use, so that gets_offline is a one time computation.)
% i = 42 ; % i can be any integer between 1 to 216 except for [72,79,90,107,111]
% y = load(sprintf('../../Data/Y/profile%d-countsN6.txt',i)) ; % load y_i data 
% y = y/sum(y) ; % normalize y 
% lambda = 1000 ; % regularization parameter 
% gets_nnreg(D_small,y,lambda) ; % solve the NNREG problem
%
% See also gets_nnls, gets_offline 
error ('gets_nnreg mexFunction not found') ;
