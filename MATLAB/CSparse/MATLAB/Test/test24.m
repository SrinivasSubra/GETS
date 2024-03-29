function test24
%TEST24 test cs_fielder
%
% Example:
%   test24
% See also: testall

% CSparse, Copyright (c) 2006-2022, Timothy A. Davis. All Rights Reserved.
% SPDX-License-Identifier: LGPL-2.1+

clear functions

index = ssget ;
[ignore f] = sort (max (index.nrows, index.ncols)) ;
f = f (1:200) ;

clf
% f = f(1)

for k = 1:length (f)
    
    i = f (k) ;
    Prob = ssget (i) ;
    disp (Prob) ;
    A = real (Prob.A) ;
    [m n] = size (A) ;
    if (m ~= n)
        continue
    end

    tic
    p1 = symrcm (A) ;
    t1 = toc ;

    tic
    p2 = cs_fiedler (A) ;
    t2 = toc ;

    rel = t2 / max (t1,1e-6) ;

    fprintf ('time: symrcm %8.3f   fiedler %8.3f  rel %8.2f\n', t1, t2, rel) ;

    A = A|A' ;

    subplot (1,3,1) ; spy (A) ;
    subplot (1,3,2) ; spy (A (p1,p1)) ;
    subplot (1,3,3) ; spy (A (p2,p2)) ;

    % evaluate the profile ...


    drawnow 
    % pause
end
