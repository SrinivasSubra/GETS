function c = cs_counts (A,mode)                                             %#ok
%CS_COUNTS column counts for sparse Cholesky factor L.
%   c = cs_counts(A) returns a vector of the column counts of L, for the
%   Cholesky factorization L*L' = A.  That is, c = sum(spones(chol(A)')),
%   except the Cholesky factorization is not computed.
%   c = cs_counts(A), returns counts for cs_chol(A).
%   c = cs_counts(A,'col'), returns counts for cs_chol(A'*A).
%   c = cs_counts(A,'sym'), same as cs_counts(A).
%
%   Example:
%       Prob = ssget ('HB/bcsstk01') ; A = Prob.A ; c = cs_counts (A)
%       full (sum (spones (chol (A)')))
%
%   See also SYMBFACT.

% CSparse, Copyright (c) 2006-2022, Timothy A. Davis. All Rights Reserved.
% SPDX-License-Identifier: LGPL-2.1+

error ('cs_counts mexFunction not found') ;
