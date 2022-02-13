@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\\out.txt"

:: Incorrect arguments count
%PROGRAM% > %OUT% && goto err
fc %OUT% %~dp0\\notEnough-output.txt || goto err
echo Test 1 passed

:: Incorrect source notation
%PROGRAM% 16 10 GO > %OUT% && goto err
fc %OUT% %~dp0\\incorrectRadix-output.txt || goto err
echo Test 2 passed

:: Standard
%PROGRAM% 6 15 -54 > %OUT% || goto err
fc %OUT% %~dp0\\standard-output.txt || goto err
echo Test 3 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
