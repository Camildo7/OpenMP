@echo off
call "C:\Program Files (x86)\Intel\oneAPI\setvars.bat" >nul 2>&1

icx /Qopenmp /O3 /Zi k1.c /Fek1.exe
icx /Qopenmp /O3 /Zi k2.c /Fek2.exe
icx /Qopenmp /O3 /Zi k2_chunk.c /Fek2_chunk.exe
icx /Qopenmp /O3 /Zi k3.c /Fek3.exe
icx /Qopenmp /O3 /Zi k3a.c /Fek3a.exe
icx /Qopenmp /O3 /Zi k4.c /Fek4.exe
icx /Qopenmp /O3 /Zi k4a.c /Fek4a.exe
icx /Qopenmp /O3 /Zi k5.c /Fek5.exe
icx /Qopenmp /O3 /Zi k5b.c /Fek5b.exe
icx /Qopenmp /O3 /Zi k5c.c /Fek5c.exe

echo.
echo === WYNIKI K1 (Sekwencyjny) ===
k1.exe
echo.
echo === WYNIKI K2 (Rownolegly) ===
k2.exe
echo.
echo === WYNIKI K2 chunk ===
k2_chunk.exe
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
echo === WYNIKI K5b ===
k5b.exe
echo.
echo === WYNIKI K5c ===
k5c.exe

pause