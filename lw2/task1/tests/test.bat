@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\\out.txt"

:: Incorrect numbers
%PROGRAM% < %~dp0\\incorrectNumbers.txt > %OUT% && goto err
fc %OUT% %~dp0\\incorrectNumbersOutputCorrect.txt || goto err
echo Test 1 passed

:: Empty string
%PROGRAM% < %~dp0\\empty.txt > %OUT% || goto err
fc %OUT% %~dp0\\emptyOutputCorrect.txt || goto err
echo Test 2 passed

:: Negative numbers
%PROGRAM% < %~dp0\\negativeNumbers.txt > %OUT% || goto err
fc %OUT% %~dp0\\negativeNumbersOutputCorrect.txt || goto err
echo Test 3 passed

:: Standard
%PROGRAM% < %~dp0\\standard.txt > %OUT% || goto err
fc %OUT% %~dp0\\standardOutputCorrect.txt || goto err
echo Test 4 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
