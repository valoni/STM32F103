@echo off
:: ����һЩ����
set x_flavor=debug
::set x_flavor=release
set x_memory=flash
set x_root=..\..\

:: �ȳ���ȡ�õ�ǰĿ¼������Ϊ������

for %%i in ("%cd%") do set x_name=%%~ni

title ����MF����[%x_name%][%x_flavor%][%x_memory%]

pushd %x_root%
call setenv_MDK.cmd
popd

if exist msbuild.log del msbuild.log /f/q

call msbuild dotnetmf.proj /t:build /p:flavor=%x_flavor%;memory=%x_memory% /maxcpucount /noLogo /v:minimal /fileLogger /flp:Verbosity=normal
:: > build.log

IF %errorlevel% == 0 (
	:: ��ɫ��ʾ�ɹ�
	echo *******************************
	echo ����ɹ�
	echo *******************************
) ELSE (
	:: ���δ�ܸ��ƵĴ���
	set x_buildout_server=%BUILD_ROOT_BASE%\Public\%x_flavor%\Server
	set x_task_name=Microsoft.SPOT.Tasks.Internal
	copy /y %x_buildout_server%\obj\%x_task_name%\__COMMON\%x_task_name%.dll %x_buildout_server%\dll\%x_task_name%.dll
	
	echo *******************************
	echo ��������뵽msbuild.log��ͨ������error�ؼ��ּ����ϸ������Ϣ��
	echo �п������±����������ʧ��Ҳ�п���ɾ�����Ŀ¼����Խ������
	echo 
	pause
	GOTO :EOF
)

:copybin
:: �����ɵ��ļ����Ƴ���
set x_buildout=%BUILD_ROOT_BASE%\THUMB2\%COMPILER_TOOL_VERSION%\le\%x_memory%\%x_flavor%\%x_name%\bin
if not exist %x_buildout% set x_buildout=%BUILD_ROOT_BASE%\THUMB2FP\%COMPILER_TOOL_VERSION%\le\%x_memory%\%x_flavor%\%x_name%\bin
set x_bindir=%x_root%..\MFBin\%x_name%

if not exist %x_bindir% md %x_bindir%
:: ����TinyBooter.bin
del %x_buildout%\*.axfdump /f/q
copy %x_buildout%\*.bin %x_bindir%\ /y
copy %x_buildout%\*.axf %x_bindir%\ /y

del %x_buildout%\*.bin /f/q
del %x_buildout%\*.axf /f/q

:: ����ER_FLASH��ER_CONFIG
set x_buildout=%x_buildout%\tinyclr.bin
copy %x_buildout%\*.* %x_bindir%\ /y
copy %x_bindir%\ER_FLASH %x_bindir%\TinyCLR.bin /y

echo ����Ѹ��Ƶ� %x_bindir%\

echo 
pause

del %x_bindir%\ER_FLASH /f/q
