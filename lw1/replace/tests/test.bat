@echo off

set PROGRAM="%~1"
set TEST_DIR="D:\\i-love-oop\\lw1\\replace\\tests"

:: Пустые значения
%PROGRAM% %TEST_DIR%\\emptyInput.txt %TEST_DIR%\\emptyOutput.txt    || goto err
fc %TEST_DIR%\\emptyOutput.txt %TEST_DIR%\\empty-output.txt || goto err
echo Test 1 passed

:: Замена одного символа
%PROGRAM% %TEST_DIR%\\oneSymbolInput.txt %TEST_DIR%\\oneSymbolOutput.txt a b || goto err
fc %TEST_DIR%\\oneSymbolOutput.txt %TEST_DIR%\\oneSymbol-output.txt || goto err
echo Test 2 passed

:: Замена нескольких символов
%PROGRAM% %TEST_DIR%\\severalSymbolsInput.txt %TEST_DIR%\\severalSymbolsOutput.txt ab cd || goto err
fc %TEST_DIR%\\severalSymbolsOutput.txt %TEST_DIR%\\severalSymbols-output.txt || goto err
echo Test 3 passed

:: Поиск пустой строки
%PROGRAM% %TEST_DIR%\\emptySearchInput.txt %TEST_DIR%\\emptySearchOutput.txt  1 || goto err
fc %TEST_DIR%\\emptySearchOutput.txt %TEST_DIR%\\emptySearch-output.txt || goto err
echo Test 4 passed

:: Не существует файла ввода
%PROGRAM% %TEST_DIR%\\notExistsInput.txt %TEST_DIR%\\notExistsOutput.txt  1 && goto err
echo Test 5 passed

:: Нагрузочный
%PROGRAM% %TEST_DIR%\\heavyInput.txt %TEST_DIR%\\heavyOutput.txt A BB || goto err
fc %TEST_DIR%\\heavyOutput.txt %TEST_DIR%\\heavy-output.txt || goto err
echo Test 6 passed

:: Стандартный
%PROGRAM% %TEST_DIR%\\standardInput.txt %TEST_DIR%\\standardOutput.txt ma mama || goto err
fc %TEST_DIR%\\standardOutput.txt %TEST_DIR%\\standard-output.txt || goto err
echo Test 7 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
