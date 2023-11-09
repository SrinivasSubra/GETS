function objfiles = gets_make
% GETS_MAKE compiles GETS and CSparse source files for use in MATLAB.
% Modified version of cs_make. 
% This function can only be used if the current directory is GETS/MATLAB/GETS.
% Returns a list of object files in ../CSparse/MATLAB/CSparse/ and the current directory. 
% 
% Example:
%       gets_make ;
%       objfiles = gets_make ;
%
% gets_make is used in gets_install.m in the GETS/MATLAB directory

if (ispc)
    obj = '.obj' ;
else
    obj = '.o' ;
end
 
mexcmd = 'mex -largeArrayDims -silent -I../../Include -I../CSparse/Include -I../CSparse/MATLAB/CSparse' ;

% CSparse source files, in ../CSparse/Source
cs = { 'cs_add', 'cs_amd', 'cs_chol', 'cs_cholsol', 'cs_counts', ...
    'cs_cumsum', 'cs_dfs', 'cs_dmperm', 'cs_droptol', 'cs_dropzeros', ...
    'cs_dupl', 'cs_entry', 'cs_etree', 'cs_fkeep', 'cs_gaxpy', 'cs_happly', ...
    'cs_house', 'cs_ipvec', 'cs_load', 'cs_lsolve', 'cs_ltsolve', 'cs_lu', ...
    'cs_lusol', 'cs_malloc', 'cs_maxtrans', 'cs_multiply', 'cs_norm', ...
    'cs_permute', 'cs_pinv', 'cs_post', 'cs_print', 'cs_pvec', 'cs_qr', ...
    'cs_qrsol', 'cs_scatter', 'cs_scc', 'cs_schol', 'cs_sqr', 'cs_symperm', ...
    'cs_tdfs', 'cs_transpose', 'cs_compress', 'cs_updown', 'cs_usolve', ...
    'cs_utsolve', 'cs_util', 'cs_reach', 'cs_spsolve', 'cs_ereach', ...
    'cs_leaf', 'cs_randperm' } ;
   
cs_mat = '../CSparse/MATLAB/CSparse/' ;
% get_install ran cs_make which created obj files lying in this folder which we will use
objfiles = [ cs_mat 'cs_mex' obj] ;
for i = 1:length (cs)
    objfiles = [objfiles ' ' cs_mat cs{i} obj] ;   %#ok
end

% GETS source files in ../../Source
getssrc = { 'gets_matvec','gets_treemult','gets_argmaxw',...
     'gets_prim', 'gets_nnls', 'gets_nnreg', 'gets_offline',...
    'gets_qrupdate','gets_qrfact','gets_qrupdate_reg','gets_qrfact_reg','gets_uppersolve', 'gets_makehouse', 'gets_applyhouse' } ;

srcdir = '../../Source/' ;
% compile gets_mex.c
eval (sprintf ('%s -O -c gets_mex.c', mexcmd)) 
objfiles = [objfiles ' ' 'gets_mex' obj] ;

for k = 1:length(getssrc)  % no need for the must compile, time stamp, compile source stuff from cs_make
    f = getssrc {k} ;
    eval (sprintf ('%s -O -c %s%s.c', mexcmd, srcdir, f))
    objfiles = [objfiles ' ' f obj] ;
end

% GETS mex functions
fprintf ('Objfiles: %s\n', objfiles) ;
cmd = sprintf ('%s -O gets_nnls_mex.c %s -output gets_nnls', mexcmd, objfiles) ;
eval (cmd) ;
cmd = sprintf ('%s -O gets_nnreg_mex.c %s -output gets_nnreg', mexcmd, objfiles) ;
eval (cmd) ;
cmd = sprintf ('%s -O gets_offline_mex.c %s -output gets_offline', mexcmd, objfiles) ;
eval (cmd) ;
fprintf ('GETS successfully compiled.\n') ;
