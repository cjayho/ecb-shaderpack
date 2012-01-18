del test\*.ps
del test\*.vs
FOR %%a IN (*.ps) DO p.bat %%a
FOR %%b IN (*.vs) DO v.bat %%b
pause