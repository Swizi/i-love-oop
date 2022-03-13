@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\\out.txt"

:: Empty
%PROGRAM% < %~dp0\\emptyInput.txt > %OUT% || goto err
fc %OUT% %~dp0\\emptyOutputCorrect.txt || goto err
echo Test 1 passed

:: Heavy
%PROGRAM% < %~dp0\\heavyInput.txt > %OUT% || goto err
fc %OUT% %~dp0\\heavyOutputCorrect.txt || goto err
echo Test 2 passed

:: Standard
%PROGRAM% < %~dp0\\standardInput.txt > %OUT% || goto err
fc %OUT% %~dp0\\standardOutputCorrect.txt || goto err
echo Test 3 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
