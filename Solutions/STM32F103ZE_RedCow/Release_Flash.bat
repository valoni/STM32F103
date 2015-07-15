::新生命嵌入式团队
::QQ群1600838
::http://www.NewLifeX.com


::@echo off
:: 设置一些参数
set x_flavor=release
::set x_flavor=debug
set x_memory=flash
set x_root=..\..\

:: 先尝试取得当前目录名，作为方案名
:: 这里的原理是把当前目录作为参数传给自己，然后从get开始执行
::call :get "%cd%.tmp"
::goto getNext
::exit
:::get
::set name=%~n1
:::getNext

for %%i in ("%cd%") do set x_name=%%~ni

title 编译MF方案[%x_name%][%x_flavor%][%x_memory%]

::goto copybin

pushd %x_root%
call setenv_MDK.cmd
popd

call msbuild /t:build /p:flavor=%x_flavor%;memory=%x_memory%
:: > build.log

echo 编译完成

:copybin
:: 把生成的文件复制出来
set x_buildout=%x_root%BuildOutput\THUMB2\MDK\le\%x_memory%\%x_flavor%\%x_name%\bin
if not exist %x_buildout% set x_buildout=%x_root%BuildOutput\THUMB2FP\MDK\le\%x_memory%\%x_flavor%\%x_name%\bin
set x_bindir=%x_root%..\MFBin\%x_name%

if not exist %x_bindir% md %x_bindir%
:: 复制TinyBooter.bin
copy %x_buildout%\*.bin %x_bindir%\ /y
copy %x_buildout%\*.axf %x_bindir%\ /y

del %x_buildout%\*.bin /f/q
del %x_buildout%\*.axf /f/q

:: 复制ER_FLASH和ER_CONFIG
set x_buildout=%x_buildout%\tinyclr.bin
copy %x_buildout%\*.* %x_bindir%\ /y
copy %x_bindir%\ER_FLASH %x_bindir%\TinyCLR.bin /y

del %x_bindir%\ER_FLASH /f/q

echo 输出已复制到 %x_bindir%\

pause