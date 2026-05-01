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
    
    long long limit = (long long)sqrt(n);
    bool* primeArray = (bool*)malloc((limit + 1) * sizeof(bool));
    
    long long repeats = 150;
    long long blockSize = 32768; 
    long long numberOfBlocks = (n - m) / blockSize;
    if ((n - m) % blockSize != 0) { numberOfBlocks++; }

    double wtime_start = omp_get_wtime();
    clock_t ctime_start = clock();

    for (long long r = 0; r < repeats; r++) {
        memset(result, true, range * sizeof(bool));
        memset(primeArray, true, (limit + 1) * sizeof(bool));

        for (long long i = 2; i * i * i * i <= n; i++) {
            if (primeArray[i]) {
                for (long long j = i * i; j * j <= n; j += i) { primeArray[j] = false; }
            }
        }

        #pragma omp parallel for schedule(dynamic)
        for (long long i = 0; i < numberOfBlocks; i++) {
            long long low = m + i * blockSize;
            long long high = m + i * blockSize + blockSize - 1;
            if (high > n) { high = n; }
            
            for (long long j = 2; j * j <= high; j++) {
                if (primeArray[j]) {
                    long long firstMultiple = (low / j);
                    if (firstMultiple <= 1) { firstMultiple = j + j; }
                    else if (low % j) { firstMultiple = (firstMultiple * j) + j; }
                    else { firstMultiple = (firstMultiple * j); }
                    
                    for (long long k = firstMultiple; k <= high; k += j) {
                        result[k - m] = false;
                    }
                }
            }
        }
    }

    clock_t ctime_stop = clock();
    double wtime_stop = omp_get_wtime();

    double avg_ctime = ((double)(ctime_stop - ctime_start) / CLOCKS_PER_SEC) / repeats;
    double avg_wtime = (wtime_stop - wtime_start) / repeats;

    long long primeCount = 0;
    for (long long i = m; i <= n; i++) { if (result[i - m]) primeCount++; }

    printf("[k5] Znaleziono: %lld\n", primeCount);
    printf("Sredni czas procesorow: %f sekund\n", avg_ctime);
    printf("Sredni czas wallclock : %f sekund\n\n", avg_wtime);

    free(result); free(primeArray);
    return 0;
}