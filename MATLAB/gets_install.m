%GETS_INSTALL: compile and install GETS and CSparse for use in MATLAB.
%   Modifed version of cs_install
%   Your current working directory must be GETS/MATLAB in order to use this
%   function.
%   
%   The directories
%
%       GETS/MATLAB/CSparse/MATLAB/CSparse
%       GETS/MATLAB/GETS
%       GETS/MATLAB/Test
%
%   are added to your MATLAB path (see the "pathtool" command to add these to
%   your path permanently, for future MATLAB sessions).
%
%   
%   Example:
%       gets_install          % install 
%   
fprintf ('Compiling and installing CSparse and GETS \n') ;
addpath ([pwd '/CSparse/MATLAB/CSparse']) ;
addpath ([pwd '/GETS']) ;
addpath ([pwd '/Test']) ;
here = pwd ; 
cd ('CSparse/MATLAB/CSparse') ;
cs_make (1) ; 
cd (here) ; 
cd ('GETS') ;
gets_make ; 
