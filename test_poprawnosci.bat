@echo off
call "C:\Program Files (x86)\Intel\oneAPI\setvars.bat" >nul 2>&1

icx /Qopenmp k1.c /Fek1.exe
icx /Qopenmp k2.c /Fek2.exe
icx /Qopenmp k3.c /Fek3.exe
icx /Qopenmp k3a.c /Fek3a.exe
icx /Qopenmp k4.c /Fek4.exe
icx /Qopenmp k4a.c /Fek4a.exe
icx /Qopenmp k5.c /Fek5.exe

echo.
echo === WYNIKI K1 (Sekwencyjny) ===
k1.exe
echo.
echo === WYNIKI K2 (Rownolegly) ===
k2.exe
echo.
echo === WYNIKI K3 ===
k3.exe
echo.
echo === WYNIKI K3a ===
k3a.exe
echo.
echo === WYNIKI K4 ===
k4.exe
echo.
echo === WYNIKI K4a ===
k4a.exe
echo.
echo === WYNIKI K5 ===
k5.exe

pause