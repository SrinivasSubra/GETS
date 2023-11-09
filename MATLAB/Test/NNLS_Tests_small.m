% NNLS_Tests_small.m
% Compares the performance of GETS solver gets_nnls and MATLAB's lsqnonneg 
% on the NNLS problem with small data (matrix of size 4096x10046) 
% and right hand side vector y. 
% Tests are performed for 211 different y vectors and the results are displayed 
% along with a histogram plot of the speed up ratios 

clear variables ; 
load('../../Data/small_input.mat') ; % load small input data 
trials = 216  ;   % Max of trials is 216, y_i data exists for i between 1 to 216 except for [72,79,90,107,111]
tM = zeros(1,trials) ; % MATLAB's lsqnonneg times 
tC = zeros(1,trials) ; % GETS times
er = zeros(1,trials) ; % x differences
eS = zeros(1,trials) ; % size of supports symmetric set differences

C_small = double(D_small.A).*(1./double(sum(D_small.A))) ; % normalize to get C from A 
N = [72,79,90,107,111] ;  % to skip loop for these values of i since y(i) doesn't exist in Y
i = 1 ;

while(i<=trials)
    
if(find(N==i))
    i = i+1 ;
end

fprintf('    Test profile number: %d \n',i) ;
y = load(sprintf('../../Data/Y/profile%d-countsN6.txt',i)) ; % load y_i
y = y/sum(y) ; % normalize y 

tic ; x2 = gets_nnls(D_small,y) ;
tC(i) = toc ; % GETS time 
fprintf ('GETS time: %g\n', tC(i)) ;

tic; x1 = lsqnonneg(C_small,y) ;  
tM(i) = toc ; % MATLAB's lsqnonneg time 
fprintf ('MATLAB lsqnonneg time: %g\n', tM(i)) ;

fprintf ('speed up ratio: %g \n', tM(i)/tC(i)) ;

er(i) = norm(x1-x2) ;
fprintf ('x difference: %g\n', er(i)) ;

I1 = find(x1) ;
I2 = find(x2) ;
s1 = length(setdiff(I1,I2)) ;
s2 = length(setdiff(I2,I1)) ;
eS(i) = s1+s2 ; 
fprintf ('size of support symmetric set difference: %d \n', eS(i)) ;
fprintf ('solution sparsity: %d \n \n', nnz(x2)) ;

i = i+1 ;

end

disp('Tests completed') ;
save('Results_NNLS_Tests_small.mat','er','eS','tM','tC') ;

%% Display the test results 

try load('Results_NNLS_Tests_small.mat')
catch
    load('Results_NNLS_Tests_small_def.mat')
end

fprintf ('\n maximum x difference: %g \n ', max(er)) ;
fprintf ('maximum size of support symmetric set difference: %g \n ', max(eS)) ;
fprintf ('minimum speed up ratio: %g \n ', min(tM./tC)) ;
fprintf ('maximum speed up ratio: %g \n ', max(tM./tC)) ;
fprintf ('mean speed up ratio: %g \n ', mean(tM./tC,'omitnan')) ;
fprintf ('median speed up ratio: %g \n ', median(tM./tC,'omitnan')) ;
histogram(tM./tC) ;
title('Histogram of speed up ratios (Small dataset)','FontSize', 22) ;
xlabel('Speed up ratio (Time_{MATLAB}/Time_{GETS})','FontSize',16) ;
ylabel('Counts','FontSize',20) ;




