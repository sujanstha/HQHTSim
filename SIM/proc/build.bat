@echo off
pushd bin
cl -Zi -Gm /Femain.exe ..\HQHT\src\*.cpp  /I ..\HQHT\include /EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib 
popd
