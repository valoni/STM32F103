::������Ƕ��ʽ�Ŷ�
::QQȺ1600838
::http://www.NewLifeX.com


::@echo off
:: ����һЩ����
set x_flavor=release
::set x_flavor=debug
set x_memory=flash
set x_root=..\..\

:: �ȳ���ȡ�õ�ǰĿ¼������Ϊ������
:: �����ԭ���ǰѵ�ǰĿ¼��Ϊ���������Լ���Ȼ���get��ʼִ��
::call :get "%cd%.tmp"
::goto getNext
::exit
:::get
::set name=%~n1
:::getNext

for %%i in ("%cd%") do set x_name=%%~ni

title ����MF����[%x_name%][%x_flavor%][%x_memory%]

::goto copybin

pushd %x_root%
call setenv_MDK.cmd
popd

call msbuild /t:build /p:flavor=%x_flavor%;memory=%x_memory%
:: > build.log

echo �������

:copybin
:: �����ɵ��ļ����Ƴ���
set x_buildout=%x_root%BuildOutput\THUMB2\MDK\le\%x_memory%\%x_flavor%\%x_name%\bin
if not exist %x_buildout% set x_buildout=%x_root%BuildOutput\THUMB2FP\MDK\le\%x_memory%\%x_flavor%\%x_name%\bin
set x_bindir=%x_root%..\MFBin\%x_name%

if not exist %x_bindir% md %x_bindir%
:: ����TinyBooter.bin
copy %x_buildout%\*.bin %x_bindir%\ /y
copy %x_buildout%\*.axf %x_bindir%\ /y

del %x_buildout%\*.bin /f/q
del %x_buildout%\*.axf /f/q

:: ����ER_FLASH��ER_CONFIG
set x_buildout=%x_buildout%\tinyclr.bin
copy %x_buildout%\*.* %x_bindir%\ /y
copy %x_bindir%\ER_FLASH %x_bindir%\TinyCLR.bin /y

del %x_bindir%\ER_FLASH /f/q

echo ����Ѹ��Ƶ� %x_bindir%\

pause