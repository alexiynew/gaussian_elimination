@echo off
set CUR_DIR=%~dp0
set PROG=%CUR_DIR%gaussian.exe
set TEST_FILE=test_out

echo run tests in "%CUR_DIR%"

for /r %CUR_DIR% %%g in (in*) do (
    set "IN_FILE=%%~nxg"

    setlocal enableDelayedExpansion
    set OUT_FILE=out!IN_FILE:~2!

    "%PROG%" < "%CUR_DIR%!IN_FILE!" > "%CUR_DIR%%TEST_FILE%"

    echo !IN_FILE:~2!:
    fc "%CUR_DIR%%TEST_FILE%" "%CUR_DIR%!OUT_FILE!"

    endlocal
)


