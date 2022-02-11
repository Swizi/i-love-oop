@echo off

set PROGRAM="%~1"
set TEST_DIR="D:\\i-love-oop\\lw1\\radix\\tests"
set OUT="%TEMP%\\out.txt"

:: Недостаточное количество аргументов
%PROGRAM% > %OUT% && goto err
fc %OUT% %TEST_DIR%\\notEnough-output.txt || goto err
echo Test 1 passed

:: Неправильная исходная кодировка
%PROGRAM% 16 10 GO > %OUT% && goto err
fc %OUT% %TEST_DIR%\\incorrectRadix-output.txt || goto err
echo Test 2 passed

:: Стандартный
%PROGRAM% 6 15 -54 > %OUT% || goto err
fc %OUT% %TEST_DIR%\\standard-output.txt || goto err
echo Test 3 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
