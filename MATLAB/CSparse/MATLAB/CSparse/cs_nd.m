function p = cs_nd (A)
%CS_ND generalized nested dissection ordering.
%   p = cs_nd(A) computes the nested dissection ordering of a matrix.  Small
%   submatrices (order 500 or less) are ordered via cs_amd.  A must be sparse
%   and symmetric (use p = cs_nd(A|A') if it is not symmetric).
%
%   Example:
%       A = delsq (numgrid ('L', 300)) ;    % matrix used in 'bench'
%       p = cs_nd (A) ;
%       cspy (A (p,p)) ;
%
%   See also CS_AMD, CS_SEP, CS_ESEP, CS_NSEP, AMD.

% CSparse, Copyright (c) 2006-2022, Timothy A. Davis. All Rights Reserved.
% SPDX-License-Identifier: LGPL-2.1+

n = size (A,1) ;
if (n == 1)
    p = 1 ;
elseif (n < 500)
    p = cs_amd (A) ;                % use cs_amd on small graphs
else
    [s a b] = cs_nsep (A) ;         % find a node separator
    a = a (cs_nd (A (a,a))) ;       % order A(a,a) recursively
    b = b (cs_nd (A (b,b))) ;       % order A(b,b) recursively
    p = [a b s] ;                   % concatenate to obtain the final ordering
end
