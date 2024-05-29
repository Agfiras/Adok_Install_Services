@echo off
echo This command just needs to run ONCE as Administrator to allow CGBC Serial port access to everyone.
echo.
net session >nul
if ERRORLEVEL 1 goto :notadmin
set key=HKLM\SYSTEM\CurrentControlSet\Enum\Acpi
for %%a in (CGT0501\21 CGT0501\22 CGT0502\22) do call :one %%a
echo DONE
goto :EOF

:one
set subkey=%key%\%1
rem echo %subkey%
reg query %subkey% >nul 2>nul
if ERRORLEVEL 1 goto :EOF
SetACL -on %subkey% -ot reg -actn setowner -ownr "n:Administrators"
SetACL -on %subkey% -ot reg -actn ace -ace "n:Administrators;p:full"
reg add %subkey% /f /v Security /t REG_BINARY /d 010004947000000080000000000000001400000002005c000400000000001400bf01120001010000000000010000000000001400a900120001010000000000050c00000000001400ff011f0001010000000000051200000000001800ff011f0001020000000000052000000020020000010200000000000520000000200200000105000000000005150000003aaa9fde42f638a7bb9bc43101020000
SetACL -on %subkey% -ot reg -actn clear -clr dacl
goto :EOF

:notadmin
echo THIS COMMAND NEEDS TO BE RUN AS ADMINISTRATOR
pause
goto :EOF
