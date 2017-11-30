@echo off
set MATLAB=C:\PROGRA~1\MATLAB\R2016a
set MATLAB_ARCH=win64
set MATLAB_BIN="C:\Program Files\MATLAB\R2016a\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=ekf_6dof_mex
set MEX_NAME=ekf_6dof_mex
set MEX_EXT=.mexw64
call setEnv.bat
echo # Make settings for ekf_6dof > ekf_6dof_mex.mki
echo COMPILER=%COMPILER%>> ekf_6dof_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> ekf_6dof_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> ekf_6dof_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> ekf_6dof_mex.mki
echo LINKER=%LINKER%>> ekf_6dof_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> ekf_6dof_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> ekf_6dof_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> ekf_6dof_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> ekf_6dof_mex.mki
echo BORLAND=%BORLAND%>> ekf_6dof_mex.mki
echo OMPFLAGS= >> ekf_6dof_mex.mki
echo OMPLINKFLAGS= >> ekf_6dof_mex.mki
echo EMC_COMPILER=msvc120>> ekf_6dof_mex.mki
echo EMC_CONFIG=optim>> ekf_6dof_mex.mki
"C:\Program Files\MATLAB\R2016a\bin\win64\gmake" -B -f ekf_6dof_mex.mk
