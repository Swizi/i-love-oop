@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\\out.txt"

:: Incorrect arguments count
%PROGRAM% %~dp0\\incorrectArgumentsCountInput.txt > %OUT% && goto err
fc %OUT% %~dp0\\incorrectArgumentsCountOutputCorrect.txt || goto err
echo Test 1 passed

:: Nonexistent input file
%PROGRAM% crypt %~dp0\\nonexistentInput.txt %~dp0\\nonexistentOutput.txt 10 > %OUT% && goto err
fc %OUT% %~dp0\\nonexistentOutputCorrect.txt || goto err
echo Test 2 passed

:: Incorrect command value
%PROGRAM% cript %~dp0\\incorrectCommandInput.txt %~dp0\\incorrectCommandOutput.txt 10 > %OUT% && goto err
fc %OUT% %~dp0\\incorrectCommandOutputCorrect.txt || goto err
echo Test 3 passed

:: Incorrect key value
%PROGRAM% decrypt %~dp0\\incorrectKeyInput.txt %~dp0\\incorrectKeyOutput.txt GO > %OUT% && goto err
fc %OUT% %~dp0\\incorrectKeyOutputCorrect.txt || goto err
echo Test 4 passed

:: Empty file
%PROGRAM% crypt %~dp0\\emptyInput.txt %~dp0\\emptyOutput.txt 0 || goto err
fc %~dp0\\emptyOutput.txt %~dp0\\emptyOutputCorrect.txt || goto err
echo Test 5 passed

:: Standard
%PROGRAM% crypt %~dp0\\standardInput.txt %~dp0\\standardOutput.txt 255 || goto err
fc %~dp0\\standardOutput.txt %~dp0\\standardOutputCorrect.txt || goto err
echo Test 6 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
