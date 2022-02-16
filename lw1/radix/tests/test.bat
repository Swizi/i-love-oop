@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\\out.txt"

:: Incorrect arguments count
%PROGRAM% > %OUT% && goto err
fc %OUT% %~dp0\\notEnough-output.txt || goto err
echo Test 1 passed

:: Incorrect source notation
%PROGRAM% 16 10 GO > %OUT% && goto err
fc %OUT% %~dp0\\incorrectSource-output.txt || goto err
echo Test 2 passed

:: Incorrect source notation
%PROGRAM% 16 40 FF > %OUT% && goto err
fc %OUT% %~dp0\\incorrectDestination-output.txt || goto err
echo Test 3 passed

:: Value overflow integer
%PROGRAM% 16 12 FFFFFFFFFFFFFFFFF > %OUT% && goto err
fc %OUT% %~dp0\\incorrectSource-output.txt || goto err
echo Test 4 passed

:: Source notation overflow integer
%PROGRAM% 10000000000000000 12 FFFFF > %OUT% && goto err
fc %OUT% %~dp0\\largeSourceNotation-output.txt || goto err
echo Test 5 passed

:: Destination notation overflow integer
%PROGRAM% 10 99999999999999 12 > %OUT% && goto err
fc %OUT% %~dp0\\largeDestinationNotation-output.txt || goto err
echo Test 6 passed

:: Zero
%PROGRAM% 16 10 0 > %OUT% || goto err
fc %OUT% %~dp0\\zero-output.txt || goto err
echo Test 7 passed

:: Max source notation and min destination notation
%PROGRAM% 2 35 11111011111 > %OUT% || goto err
fc %OUT% %~dp0\\max-min-output.txt || goto err
echo Test 8 passed

:: Standard
%PROGRAM% 6 15 -54 > %OUT% || goto err
fc %OUT% %~dp0\\standard-output.txt || goto err
echo Test 9 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1
