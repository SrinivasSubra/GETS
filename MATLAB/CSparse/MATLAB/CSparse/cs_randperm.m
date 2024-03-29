function p = cs_randperm (n, seed)                                          %#ok
%CS_RANDPERM random permutation.
%   p = cs_randperm (n) returns a repeatable random permutation of 1:n.
%   p = cs_randperm (n,seed) returns the random permutation using the given
%   seed for the random number generator (try cs_randperm (n,rand)), where
%   seed is not 0 or -1.  Two special cases are not random permutations at all:
%   p=cs_randperm (n,0) is 1:n, and p=cs_randperm (n,-1) is n:-1:1.
%   This function does not change RAND's state.
%
%   Example:
%       p = cs_randperm (10)
%
%   See also CS_DMPERM, RAND, RANDPERM

% CSparse, Copyright (c) 2006-2022, Timothy A. Davis. All Rights Reserved.
% SPDX-License-Identifier: LGPL-2.1+

error ('cs_randperm mexFunction not found') ;
