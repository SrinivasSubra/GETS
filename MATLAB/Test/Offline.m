% Offline.m
% Performs the offline computations using gets_offline. 
% Takes the matrix A as input and outputs the sparse representation D in 
% the form of a MATLAB struct. D will be the input for the solver gets_nnls. 
% See the treedata struct declaration in GETS/Include/gets.h
% For example, the treedata struct D for small data has the fields: 
%         m: 4096
%         n: 10046
%     bposp: [1×10047 int64]
%     bnegp: [1×10047 int64]
%     bposi: [1×2889340 int16]
%     bnegi: [1×2843978 int16]
%        xp: [1×10047 int64]
%        xi: [1×683878 int16]
%        xx: [1×683878 int8]
%         A: [4096×10046 int8]
%      diag: [1×10046 int64]
%       ipt: [1×10046 int64]
%      post: [1×10046 int64] 

%% Small data (runtime: ~2min) 

load('../../Data/A_small.mat') ;
tic; D_small = gets_offline(As) ; T_os = toc ; 
save('small_input.mat','D_small') ;

%% Large data (runtime: 7.8904 hrs)

load('../../Data/A_large.mat') ;
tic ; D_large = gets_offline(AL) ; T_oL = toc ; 
save('Large_input.mat','D_large') ;

