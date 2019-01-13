@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

set TEST_IN="lw2_tests\input"
set TEST_OUT="lw2_tests\output"

%PROGRAM% %TEST_IN%1.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%1.txt || goto err

%PROGRAM% %TEST_IN%2.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%2.txt || goto err

%PROGRAM% %TEST_IN%3.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%3.txt || goto err

%PROGRAM% %TEST_IN%4.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%4.txt || goto err

%PROGRAM% %TEST_IN%5.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%5.txt || goto err

%PROGRAM% %TEST_IN%6.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%6.txt || goto err

echo All tests passed!
exit /B 0

:err
echo Program testing failed...
exit /B 1