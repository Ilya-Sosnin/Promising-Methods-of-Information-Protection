#include "generator/BigNumGenerator.h"
#include <iostream>

int main() {
    mpz_t a;
    mpz_init(a);

    gmp_randstate_t state;
    gmp_randinit_default(state);

    mpz_urandomb(a, state, 256);
    gmp_printf("Generated num: %Zd", a);
    return 0;
} 