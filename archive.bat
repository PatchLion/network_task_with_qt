echo off
cls

set NetworkTaskLib_Version=1.0.0

echo NetworkTaskLib version=%NetworkTaskLib_Version%

RD /S /Q ..\archive\%NetworkTaskLib_Version%

MD ..\archive\%NetworkTaskLib_Version%\win32\debug
MD ..\archive\%NetworkTaskLib_Version%\win32\release
MD ..\archive\%NetworkTaskLib_Version%\x64\debug
MD ..\archive\%NetworkTaskLib_Version%\x64\release

set WIN32_DIR=..\archive\%NetworkTaskLib_Version%\win32
set WIN64_DIR=..\archive\%NetworkTaskLib_Version%\x64
set INCLUDE_DIR=..\archive\%NetworkTaskLib_Version%\include

echo copy include files
echo D | xcopy /E /Y /Q .\include %INCLUDE_DIR%

echo copy 32bit files

copy .\bin\win32\debug\HowToUse.exe %WIN32_DIR%\debug\HowToUse.exe
copy .\bin\win32\release\HowToUse.exe %WIN32_DIR%\release\HowToUse.exe
copy .\lib\win32\debug\NetworkTaskLib.lib %WIN32_DIR%\debug\NetworkTaskLib.lib
copy .\lib\win32\release\NetworkTaskLib.lib %WIN32_DIR%\release\NetworkTaskLib.lib

echo copy 64bit files

copy .\bin\x64\debug\HowToUse.exe %WIN64_DIR%\debug\HowToUse.exe
copy .\bin\x64\release\HowToUse.exe %WIN64_DIR%\release\HowToUse.exe
copy .\lib\x64\debug\NetworkTaskLib.lib %WIN64_DIR%\debug\NetworkTaskLib.lib
copy .\lib\x64\release\NetworkTaskLib.lib %WIN64_DIR%\release\NetworkTaskLib.lib

pause