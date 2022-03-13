@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\\out.txt"

:: Standard
%PROGRAM% > %OUT% || goto err
fc %OUT% %~dp0\\standardOutputCorrect.txt || goto err
echo Test 1 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
