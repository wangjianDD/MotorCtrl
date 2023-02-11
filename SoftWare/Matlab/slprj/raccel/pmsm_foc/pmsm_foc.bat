@echo off
set "VSCMD_START_DIR=%CD%"
call "D:\IDE\visual_studio\vs\VC\Auxiliary\Build\VCVARSALL.BAT" amd64

cd .
nmake -f pmsm_foc.mk  RSIM_SOLVER_SELECTION=2 PCMATLABROOT="D:\\software\\Matlab" EXTMODE_STATIC_ALLOC=0 EXTMODE_STATIC_ALLOC_SIZE=1000000 EXTMODE_TRANSPORT=0 TMW_EXTMODE_TESTING=0 RSIM_PARAMETER_LOADING=1 OPTS="-DTGTCONN -DIS_SIM_TARGET -DNRT -DRSIM_PARAMETER_LOADING -DRSIM_WITH_SL_SOLVER -DENABLE_SLEXEC_SSBRIDGE=1 -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -DON_TARGET_WAIT_FOR_START=0 -DTID01EQ=0"
@if errorlevel 1 goto error_exit
exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1