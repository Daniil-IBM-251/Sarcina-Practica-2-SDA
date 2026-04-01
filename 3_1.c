#include <stdio.h>
#include <windows.h>
#include <gmp.h>

// Algoritm Fast Doubling
void fib_fast(unsigned int n, mpz_t fn, mpz_t fn1) {
    if (n == 0) {
        mpz_set_ui(fn, 0);
        mpz_set_ui(fn1, 1);
        return;
    }

    mpz_t a, b, c, d;
    mpz_inits(a, b, c, d, NULL);

    fib_fast(n >> 1, a, b);

    mpz_mul_ui(c, b, 2);
    mpz_sub(c, c, a);
    mpz_mul(c, c, a);

    mpz_mul(d, a, a);
    mpz_addmul(d, b, b);

    if (n & 1) {
        mpz_set(fn, d);
        mpz_add(fn1, c, d);
    } else {
        mpz_set(fn, c);
        mpz_set(fn1, d);
    }

    mpz_clears(a, b, c, d, NULL);
}

int main() {
    unsigned int N;
    printf("Introdu poziția N: ");
    scanf("%u", &N);

    mpz_t fn, fn1;
    mpz_inits(fn, fn1, NULL);

    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    fib_fast(N, fn, fn1);
    gmp_printf("Fib(%u) = %Zd\n", N, fn);
    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

    gmp_printf("Fib(%u) calculat în %.9f secunde\n", N, elapsed);

    mpz_clears(fn, fn1, NULL);
    return 0;
}
