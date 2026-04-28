#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main() {
    long long m = 2, n = 100000000;
    long long range = n - m + 1;
    bool* result = (bool*)malloc(range * sizeof(bool));
    memset(result, true, range * sizeof(bool));
    
    long long limit = (long long)sqrt(n);
    bool* primeArray = (bool*)malloc((limit + 1) * sizeof(bool));
    memset(primeArray, true, (limit + 1) * sizeof(bool));
    
    // --- START ZEGAROW ---
    double wtime_start = omp_get_wtime();
    clock_t ctime_start = clock();

    for (long long i = 2; i * i <= n; i++) {
        for (long long j = 2; j * j <= i; j++) {
            if (primeArray[j] && i % j == 0) { primeArray[i] = false; break; }
        }
    }
    
    #pragma omp parallel for schedule(dynamic)
    for (long long i = m; i <= n; i++) {
        for (long long j = 2; j * j <= i; j++) {
            if (primeArray[j] && i % j == 0) { result[i - m] = false; break; }
        }
    }

    // --- STOP ZEGAROW ---
    clock_t ctime_stop = clock();
    double wtime_stop = omp_get_wtime();

    long long primeCount = 0;
    for (long long i = m; i <= n; i++) { if (result[i - m]) primeCount++; }

    printf("[k2] Znaleziono: %lld\n", primeCount);
    printf("Czas procesorow: %f sekund\n", ((double)(ctime_stop - ctime_start) / CLOCKS_PER_SEC));
    printf("Czas wallclock : %f sekund\n\n", wtime_stop - wtime_start);

    free(result); free(primeArray);
    return 0;
}