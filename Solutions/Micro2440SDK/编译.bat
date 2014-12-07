@echo off
:: ����һЩ����
set x_flavor=release
set x_memory=flash
set x_root=..\..\

:: �ȳ���ȡ�õ�ǰĿ¼������Ϊ������

for %%i in ("%cd%") do set x_name=%%~ni

title ����MF����[%x_name%][%x_flavor%][%x_memory%]

pushd %x_root%
call setenv_MDK.cmd
popd

:: ׼��Feedback��������뾯��
set feedback=%CLRROOT%\tools\make\Feedback\%x_name%_%COMPILER_TOOL_VERSION%.feedback
if Not Exist %feedback% echo feedback > %feedback%
set feedback=%CLRROOT%\tools\make\Feedback\%x_name%_%COMPILER_TOOL_VERSION%_loader.feedback
if Not Exist %feedback% echo feedback > %feedback%

if exist msbuild.log del msbuild.log /f/q

echo ��ʼ����......
call msbuild TinyCLR\TinyCLR.proj /t:build /p:flavor=%x_flavor%;memory=%x_memory% /maxcpucount /noLogo /v:minimal /fileLogger /flp:Verbosity=normal

IF %errorlevel% == 0 (
	:: ��ɫ��ʾ�ɹ�
	echo *******************************
	echo ����ɹ�
	echo *******************************
) ELSE (
	echo *******************************
	echo ��������뵽msbuild.log��ͨ������error�ؼ��ּ����ϸ������Ϣ��
	echo �п������±����������ʧ��Ҳ�п���ɾ�����Ŀ¼����Խ������
	echo 
	pause
	GOTO :EOF
)

:copybin
:: �����ɵ��ļ����Ƴ���
set x_buildout=%BUILD_ROOT_BASE%\%x_name%\%x_flavor%\bin
set x_bindir=%x_root%..\MFBin\%x_name%

if not exist %x_bindir% md %x_bindir%
:: ����TinyBooter.bin
::del %x_buildout%\*.axfdump /f/q
::copy %x_buildout%\*.bin %x_bindir%\ /y
::copy %x_buildout%\*.axf %x_bindir%\ /y

::del %x_buildout%\*.bin /f/q
::del %x_buildout%\*.axf /f/q

:: ����ER_FLASH��ER_CONFIG
copy %x_buildout%\tinyclr.bin\ER_FLASH %x_bindir%\TinyCLR.bin /y
copy %x_buildout%\tinyclr.bin\ER_CONFIG %x_bindir%\Config.bin /y

copy %x_buildout%\tinyclr.hex\ER_FLASH %x_bindir%\TinyCLR.hex /y
copy %x_buildout%\tinyclr.hex\ER_CONFIG %x_bindir%\Config.hex /y

echo ����Ѹ��Ƶ� %x_bindir%\

echo 
pause

::del %x_bindir%\ER_FLASH /f/q
