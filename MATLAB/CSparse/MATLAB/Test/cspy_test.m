function cspy_test
%CSPY_TEST test cspy and cs_dmspy
% Example
%   cspy_test
% See also: testall

% CSparse, Copyright (c) 2006-2022, Timothy A. Davis. All Rights Reserved.
% SPDX-License-Identifier: LGPL-2.1+

index = ssget ;

[ignore f] = sort (max (index.nrows, index.ncols)) ;

clf

% f = f (523:end) ;
% f = f ((find (f == 938)):end) ;

for i = f

    Prob = ssget (i,index) ;
    disp (Prob) ;
    A = Prob.A ;
    try
        subplot (1,4,1) ; cspy (A) ;
        drawnow
        subplot (1,4,2) ; cspy (A,64) ;
        drawnow
        subplot (1,4,3) ; cs_dmspy (A) ;
        drawnow
        subplot (1,4,4) ; cs_dmspy (A,0) ;
        drawnow
    catch
        fprintf ('failed...\n') ;
    end

    [m n] = size (A) ;
    if (m == n & nnz (diag (A)) == n)                                       %#ok
        p = cs_dmperm (A) ;
        if (any (p ~= 1:n))
            error ('!') ;
        end
        [p q r s cc rr] = cs_dmperm (A) ;                                   %#ok
        if (any (p ~= q))
            error ('not sym!') ;
        end
    end

    drawnow
end
