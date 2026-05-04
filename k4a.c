#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main() {
    // long long m = 2, n = 100000000;
    // long long m = 2, n = 50000000;
    long long m = 50000000, n = 100000000;
    long long range = n - m + 1;
    bool* result = (bool*)malloc(range * sizeof(bool));
    
    long long limit = (long long)sqrt(n);
    bool* primeArray = (bool*)malloc((limit + 1) * sizeof(bool));
    
    long long repeats = 50;

    double wtime_start = omp_get_wtime();
    clock_t ctime_start = clock();

    for (long long r = 0; r < repeats; r++) {
        memset(result, true, range * sizeof(bool));
        memset(primeArray, true, (limit + 1) * sizeof(bool));

        for (long long i = 2; i * i * i * i <= n; i++) {
            if (primeArray[i]) {
                for (long long j = i * i; j * j <= n; j += i) { 
                    primeArray[j] = false; 
                }
            }
        }

        #pragma omp parallel for schedule(dynamic)
        for (long long i = 2; i <= limit; i++) {
            if (primeArray[i]) {
                long long firstMultiple = (m / i);
                if (firstMultiple <= 1) { firstMultiple = i + i; }
                else if (m % i) { firstMultiple = (firstMultiple * i) + i; }
                else { firstMultiple = (firstMultiple * i); }
                
                for (long long j = firstMultiple; j <= n; j += i) {
                    if (result[j-m]) result[j-m] = false; 
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

    printf("[k4a] Znaleziono: %lld\n", primeCount);
    printf("Sredni czas procesorow: %f sekund\n", avg_ctime);
    printf("Sredni czas wallclock : %f sekund\n\n", avg_wtime);
    
    free(result); 
    free(primeArray);
    return 0;
}