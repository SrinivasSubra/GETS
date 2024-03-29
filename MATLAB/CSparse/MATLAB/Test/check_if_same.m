function check_if_same (p1,p2)
%CHECK_IF_SAME check if two inputs are identical or not
%
% Example:
%   check_if_same (1:5, 2:6)
% See also: testall

% CSparse, Copyright (c) 2006-2022, Timothy A. Davis. All Rights Reserved.
% SPDX-License-Identifier: LGPL-2.1+

    if (isempty (p1))
        if (~isempty (p2))
            p1          %#ok
            p2          %#ok
            error ('empty!') ;
        end
    elseif (any (p1 ~= p2))
        p1              %#ok
        p2              %#ok
        error ('!') ;
    end

