function D = gets_offline (A)
%GETS_OFFLINE construct a sparse representation of an integer DNA matrix of k-mer counts for GETS
%
%   D = gets_offline (A)
%
% Input matrix A must be given as an int8 matrix in MATLAB. 
% Performs the offline computations: Takes the matrix A as input 
% and outputs the sparse representation D in the form of a MATLAB struct. 
% D will be the input for the solver gets_nnls or gets_nnreg.  
% See the treedata struct declaration in GETS/Include/gets.h
% For example, the treedata struct D for small data has the fields: 
%
%         m: 4096              % number of rows 
%         n: 10046             % number of columns 
%     bposp: [1×10047 int64]   % column pointers for binary +1 entries of Diff
%     bnegp: [1×10047 int64]   % column pointers for binary -1 entries of Diff
%     bposi: [1×2889340 int16] % row indices for binary +1 entries of Diff
%     bnegi: [1×2843978 int16] % row indices for binary -1 entries of Diff
%        xp: [1×10047 int64]   % column pointers for non binary entries of Diff
%        xi: [1×683878 int16]  % row indices for non binary entries of Diff
%        xx: [1×683878 int8]   % numerical values for non binary entries of Diff
%         A: [4096×10046 int8] % reordered unnormalized integer matrix A
%      diag: [1×10046 int64]   % normalization factors: column sums of reordered A
%       ipt: [1×10046 int64]   % parent array in the reordered tree, ipt = invpost(parent(post)))
%      post: [1×10046 int64]   % post ordering of the MST
%
% The offline computations create the treedata struct for efficient
% representation of genomic data. This enables fast computation of A'*r in 
% gets_treemult.c (see struct definition is gets.h). 
% gets_offline computes and stores the minimum spanning tree, post ordering of the tree vertices, 
% reordered matrix A and column sums for diag, parent array in the
% reordered tree and the sparse components for the Diff matrix. 
% Diff(:,j) = A(:,j) - A(:,k), where k = ipt(j), k is the parent of j in the reordered tree
% Diff = Dbpos + Dbneg + Dx, where Dbpos and Dneg are sparse binary +1 and -1 matrices respectively. 
% Dx is a sparse matrix with non-binary values.
%
% Example:
%     load('../../Data/A_small.mat') ; % load small matrix data from mat file
%     D_small = gets_offline(As) ; % As is the small int8 matrix of size 4096-by-10046
%     save('small_input.mat','D_small') ; % save D_small to a mat-file for future use  
%
% See also gets_nnls, gets_nnreg 
error ('gets_offline mexFunction not found') ;

