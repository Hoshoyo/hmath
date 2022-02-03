@echo off

call cl /I.. /nologo /Zi main.c
call cl /I.. /O2 /nologo /Zi speed.c
call cl /O2 /nologo /Zi gm.c