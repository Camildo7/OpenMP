@echo off
echo ====================================================
echo   AUTOMATYZACJA PROJEKTU: OPENMP + VTUNE (ALL CORES)
echo ====================================================
echo.

echo [1/3] Ladowanie srodowiska Intel oneAPI...
call "C:\Program Files (x86)\Intel\oneAPI\setvars.bat" >nul 2>&1
echo Gotowe.
echo.

echo [2/3] Kompilacja kodow zrodlowych (k1 - k5)...
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
echo Gotowe.
echo.

set OMP_NUM_THREADS=16
echo Wykorzystywane watki OpenMP: %OMP_NUM_THREADS%
echo.

echo [3/3] Rozpoczecie zbierania danych Microarchitecture Exploration...
echo Usuwanie starych folderow wynikowych...
if exist wynik_k1 rmdir /s /q wynik_k1
if exist wynik_k2 rmdir /s /q wynik_k2
if exist wynik_k2_chunk rmdir /s /q wynik_k2_chunk
if exist wynik_k3 rmdir /s /q wynik_k3
if exist wynik_k3a rmdir /s /q wynik_k3a
if exist wynik_k4 rmdir /s /q wynik_k4
if exist wynik_k4a rmdir /s /q wynik_k4a
if exist wynik_k5 rmdir /s /q wynik_k5
if exist wynik_k5b rmdir /s /q wynik_k5b
if exist wynik_k5c rmdir /s /q wynik_k5c
echo.

echo Profilowanie k1...
vtune -collect uarch-exploration -result-dir wynik_k1 -- k1.exe
echo Profilowanie k2...
vtune -collect uarch-exploration -result-dir wynik_k2 -- k2.exe
echo Profilowanie k2_chunk...
vtune -collect uarch-exploration -result-dir wynik_k2_chunk -- k2_chunk.exe
echo Profilowanie k3...
vtune -collect uarch-exploration -result-dir wynik_k3 -- k3.exe
echo Profilowanie k3a...
vtune -collect uarch-exploration -result-dir wynik_k3a -- k3a.exe
echo Profilowanie k4...
vtune -collect uarch-exploration -result-dir wynik_k4 -- k4.exe
echo Profilowanie k4a...
vtune -collect uarch-exploration -result-dir wynik_k4a -- k4a.exe
echo Profilowanie k5...
vtune -collect uarch-exploration -result-dir wynik_k5 -- k5.exe
echo Profilowanie k5b...
vtune -collect uarch-exploration -result-dir wynik_k5b -- k5b.exe
echo Profilowanie k5c...
vtune -collect uarch-exploration -result-dir wynik_k5c -- k5c.exe

echo.
echo ====================================================
echo   ZAKONCZONO! Foldery wynikowe sa gotowe.
echo ====================================================

echo.
echo [4/4] Generowanie raportow HTML dla uzytkownikow macOS...
vtune -report summary -r wynik_k1 -format=html -report-output raport_k1_4.html
vtune -report summary -r wynik_k2 -format=html -report-output raport_k2_4.html
vtune -report summary -r wynik_k2_chunk -format=html -report-output raport_k2_chunk_4.html
vtune -report summary -r wynik_k3 -format=html -report-output raport_k3_4.html
vtune -report summary -r wynik_k3a -format=html -report-output raport_k3a_4.html
vtune -report summary -r wynik_k4 -format=html -report-output raport_k4_4.html
vtune -report summary -r wynik_k4a -format=html -report-output raport_k4a_4.html
vtune -report summary -r wynik_k5 -format=html -report-output raport_k5_4.html
vtune -report summary -r wynik_k5b -format=html -report-output raport_k5b_4.html
vtune -report summary -r wynik_k5c -format=html -report-output raport_k5c_4.html

echo.
echo Raporty HTML zostaly wygenerowane w glownym folderze!
pause