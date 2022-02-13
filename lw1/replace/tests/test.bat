@echo off

set PROGRAM="%~1"

:: Empty values
%PROGRAM% %~dp0\\emptyInput.txt %~dp0\\emptyOutput.txt    || goto err
fc %~dp0\emptyOutput.txt %~dp0\\empty-output.txt || goto err
echo Test 1 passed

:: One symbol
%PROGRAM% %~dp0\\oneSymbolInput.txt %~dp0\\oneSymbolOutput.txt a b || goto err
fc %~dp0\\oneSymbolOutput.txt %~dp0\\oneSymbol-output.txt || goto err
echo Test 2 passed

:: Several symbols
%PROGRAM% %~dp0\\severalSymbolsInput.txt %~dp0\\severalSymbolsOutput.txt ab cd || goto err
fc %~dp0\\severalSymbolsOutput.txt %~dp0\\severalSymbols-output.txt || goto err
echo Test 3 passed

:: Empty search string
%PROGRAM% %~dp0\\emptySearchInput.txt %~dp0\\emptySearchOutput.txt  1 || goto err
fc %~dp0\\emptySearchOutput.txt %~dp0\\emptySearch-output.txt || goto err
echo Test 4 passed

:: Not exists input file
%PROGRAM% %~dp0\\notExistsInput.txt %~dp0\\notExistsOutput.txt  1 && goto err
echo Test 5 passed

:: Heavy(1 billion letters)
%PROGRAM% %~dp0\\heavyInput.txt %~dp0\\heavyOutput.txt A BB || goto err
fc %~dp0\\heavyOutput.txt %~dp0\\heavy-output.txt || goto err
echo Test 6 passed

:: Standard
%PROGRAM% %~dp0\\standardInput.txt %~dp0\\standardOutput.txt ma mama || goto err
fc %~dp0\\standardOutput.txt %~dp0\\standard-output.txt || goto err
echo Test 7 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
