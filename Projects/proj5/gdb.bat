@echo off
set exe=%1
IF [%1]==[] set exe=a.exe
gdb.exe %exe% -x "gdb commands.gtxt" 

