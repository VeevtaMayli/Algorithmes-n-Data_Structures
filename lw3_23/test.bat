@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

set TEST_IN="lw3_tests\input"
set TEST_OUT="lw3_tests\output"

%PROGRAM% %TEST_IN%1.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%1.txt

%PROGRAM% %TEST_IN%2.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%2.txt

%PROGRAM% %TEST_IN%3.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%3.txt

%PROGRAM% %TEST_IN%4.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%4.txt

%PROGRAM% %TEST_IN%5.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%5.txt

%PROGRAM% %TEST_IN%6.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%6.txt

%PROGRAM% %TEST_IN%7.txt > %OUT% || goto err
fc %OUT% %TEST_OUT%7.txt

echo All tests passed!
exit /B 0

:err
echo Program testing failed...
exit /B 1