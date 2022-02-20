@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\\out.txt"

:: Nonexistent file
%PROGRAM% %~dp0\\nonexistentInput.txt > %OUT% && goto err
fc %OUT% %~dp0\\nonexistentOutput.txt || goto err
echo Test 1 passed

:: Incorrect vertical dimension
%PROGRAM% %~dp0\\incorrectVerticalDimensionInput.txt > %OUT% && goto err
fc %OUT% %~dp0\\incorrectVerticalDimensionOutput.txt || goto err
echo Test 2 passed

:: Incorrect horizontal dimension
%PROGRAM% %~dp0\\incorrectHorizontalDimensionInput.txt > %OUT% && goto err
fc %OUT% %~dp0\\incorrectHorizontalDimensionOutput.txt || goto err
echo Test 3 passed

:: Incorrect matrix value
%PROGRAM% %~dp0\\incorrectMatrixValueInput.txt > %OUT% && goto err
fc %OUT% %~dp0\\incorrectMatrixValueOutput.txt || goto err
echo Test 4 passed

:: Incorrect arguments count
%PROGRAM% 1 2 > %OUT% && goto err
fc %OUT% %~dp0\\incorrectArgumentsCountOutput.txt || goto err
echo Test 5 passed

:: Cant calculate inversed matrix
%PROGRAM% %~dp0\\cantCalculateInversedMatrixInput.txt > %OUT% && goto err
fc %OUT% %~dp0\\cantCalculateInversedMatrixOutput.txt || goto err
echo Test 6 passed

:: Standard
%PROGRAM% %~dp0\\standardInput.txt > %OUT% || goto err
fc %OUT% %~dp0\\standardOutput.txt || goto err
echo Test 7 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
