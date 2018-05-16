@echo off
if exist %1 (
	make clean gdb(%1)
) else (
	make gdb%2(%1)
)

