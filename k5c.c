#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main() {
    long long m = 3, n = 100000000;
    
    long long rangeOdds = (n - m) / 2 + 1;
    bool* result = (bool*)malloc(rangeOdds * sizeof(bool));
    
    long long limit = (long long)sqrt(n);
    bool* primeArray = (bool*)malloc((limit + 1) * sizeof(bool));
    
    long long repeats = 1000;
    long long blockSize = 32768;
    long long numberOfBlocks = rangeOdds / blockSize;
    if (rangeOdds % blockSize != 0) { numberOfBlocks++; }

    double wtime_start = omp_get_wtime();
    clock_t ctime_start = clock();

    for (long long r = 0; r < repeats; r++) {
        memset(result, true, rangeOdds * sizeof(bool));
        memset(primeArray, true, (limit + 1) * sizeof(bool));

        for (long long i = 2; i * i * i * i <= n; i++) {
            if (primeArray[i]) {
                for (long long j = i * i; j * j <= n; j += i) { primeArray[j] = false; }
            }
        }

        #pragma omp parallel for schedule(dynamic)
        for (long long i = 0; i < numberOfBlocks; i++) {
            long long lowIndex = i * blockSize;
            long long highIndex = lowIndex + blockSize - 1;
            if (highIndex >= rangeOdds) highIndex = rangeOdds - 1;
            
            long long low = m + lowIndex * 2;
            long long high = m + highIndex * 2;
            
            for (long long j = 3; j * j <= high; j += 2) {
                if (primeArray[j]) {
                    long long firstMultiple = (low / j);
                    if (firstMultiple < j) { firstMultiple = j; }
                    
                    long long start = firstMultiple * j;
                    if (start < low) start += j;
                    if (start % 2 == 0) start += j; 
                    
                    long long step = j * 2;
                    
                    for (long long k = start; k <= high; k += step) {
                        result[(k - m) / 2] = false;
                    }
                }
            }
        }
    }

    clock_t ctime_stop = clock();
    double wtime_stop = omp_get_wtime();

    double avg_ctime = ((double)(ctime_stop - ctime_start) / CLOCKS_PER_SEC) / repeats;
    double avg_wtime = (wtime_stop - wtime_start) / repeats;

    long long primeCount = 1;
    for (long long i = 0; i < rangeOdds; i++) { 
        if (result[i]) primeCount++; 
    }

    printf("[k5c - OddsOnly] Znaleziono: %lld\n", primeCount);
    printf("Sredni czas procesorow: %f sekund\n", avg_ctime);
    printf("Sredni czas wallclock : %f sekund\n\n", avg_wtime);

    free(result); free(primeArray);
    return 0;
}