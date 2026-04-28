#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

int main() {
    long long m = 2;
    long long n = 100000000;
    long long range = n - m + 1;
    
    bool* result = (bool*)malloc(range * sizeof(bool));
    for(long long i = 0; i < range; i++) result[i] = true;
    
    long long limit = (long long)sqrt(n);
    bool* primeArray = (bool*)malloc((limit + 1) * sizeof(bool));
    for(long long i = 0; i <= limit; i++) primeArray[i] = true;
    
    for (long long i = 2; i * i <= n; i++) {
        for (long long j = 2; j * j <= i; j++) {
            if (primeArray[j] && i % j == 0) {
                primeArray[i] = false;
                break;
            }
        }
    }
    
    #pragma omp parallel for schedule(dynamic)
    for (long long i = m; i <= n; i++) {
        for (long long j = 2; j * j <= i; j++) {
            if (primeArray[j] && i % j == 0) {
                result[i - m] = false;
                break;
            }
        }
    }
    
    long long primeCount = 0;
    
    // Zliczanie i wypisywanie liczb pierwszych.
    for (long long i = m; i <= n; i++) {
        if (result[i - m] == true) {
            primeCount++;
            // printf("%lld ", i);
        }
    }
    printf("\nLacznie znaleziono: %lld\n", primeCount);

    free(result);
    free(primeArray);
    return 0;
}