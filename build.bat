@echo off
echo ========================================================
echo   Compiling DSA Assignment Programs (C & C++)
echo ========================================================

echo Compiling Q1 Stack in C...
gcc -Wall -Wextra -std=c99 q1_stack\stack.c -o q1_stack\stack_c.exe
if %ERRORLEVEL% EQU 0 (echo [OK] q1_stack\stack_c.exe generated) else (echo [FAIL] Error compiling stack.c)

echo Compiling Q1 Stack in C++...
g++ -Wall -Wextra -std=c++11 q1_stack\stack.cpp -o q1_stack\stack_cpp.exe
if %ERRORLEVEL% EQU 0 (echo [OK] q1_stack\stack_cpp.exe generated) else (echo [FAIL] Error compiling stack.cpp)

echo Compiling Q2 Circular Queue in C...
gcc -Wall -Wextra -std=c99 q2_circular_queue\circular_queue.c -o q2_circular_queue\queue_c.exe
if %ERRORLEVEL% EQU 0 (echo [OK] q2_circular_queue\queue_c.exe generated) else (echo [FAIL] Error compiling circular_queue.c)

echo Compiling Q2 Circular Queue in C++...
g++ -Wall -Wextra -std=c++11 q2_circular_queue\circular_queue.cpp -o q2_circular_queue\queue_cpp.exe
if %ERRORLEVEL% EQU 0 (echo [OK] q2_circular_queue\queue_cpp.exe generated) else (echo [FAIL] Error compiling circular_queue.cpp)

echo ========================================================
echo   Compilation complete! Run executables to test.
echo ========================================================
pause
