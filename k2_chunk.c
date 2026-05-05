#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 50
#endif

int main() {
    long long m = 2, n = 100000000;
    // long long m = 2, n = 50000000;
    // long long m = 50000000, n = 100000000;
    long long range = n - m + 1;
    bool* result = (bool*)malloc(range * sizeof(bool));
    
    long long limit = (long long)sqrt(n);
    bool* primeArray = (bool*)malloc((limit + 1) * sizeof(bool));
    
    long long repeats = 6;

    double wtime_start = omp_get_wtime();
    clock_t ctime_start = clock();

    for (long long r = 0; r < repeats; r++) {
        memset(result, true, range * sizeof(bool));
        memset(primeArray, true, (limit + 1) * sizeof(bool));

        for (long long i = 2; i * i <= n; i++) {
            for (long long j = 2; j * j <= i; j++) {
                if (primeArray[j] && i % j == 0) { primeArray[i] = false; break; }
            }
        }
        
        #pragma omp parallel for schedule(dynamic, CHUNK_SIZE)
        for (long long i = m; i <= n; i++) {
            for (long long j = 2; j * j <= i; j++) {
                if (primeArray[j] && i % j == 0) { result[i - m] = false; break; }
            }
        }
    }

    clock_t ctime_stop = clock();
    double wtime_stop = omp_get_wtime();

    double avg_ctime = ((double)(ctime_stop - ctime_start) / CLOCKS_PER_SEC) / repeats;
    double avg_wtime = (wtime_stop - wtime_start) / repeats;

    long long primeCount = 0;
    for (long long i = m; i <= n; i++) { if (result[i - m]) primeCount++; }

    printf("[k2_chunk - Size: %d] Znaleziono: %lld\n", CHUNK_SIZE, primeCount);
    printf("Sredni czas procesorow: %f sekund\n", avg_ctime);
    printf("Sredni czas wallclock : %f sekund\n\n", avg_wtime);

    free(result); free(primeArray);
    return 0;
}