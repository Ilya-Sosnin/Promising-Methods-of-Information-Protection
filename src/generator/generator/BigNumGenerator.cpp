#include "generator/BigNumGenerator.h"
#include <fstream>
#include <random>

BigNumGenerator::BigNumGenerator() {
    std::random_device rd;
    mpz_inits(q, p, g, 0);
    gmp_randinit_default(rs);
    gmp_randseed_ui(rs, rd());
};

BigNumGenerator::~BigNumGenerator() {
    mpz_clears(q, p, g, 0);
    gmp_randclear(rs);
};

void BigNumGenerator::generateParams() {
    generateP();
    findMultiplicativeGenerator();
    // findCyclicGenerator();
}

void BigNumGenerator::saveParams() {
    FILE *file = fopen("params.key", "w");

    if (file == nullptr)
        throw std::runtime_error("Cannot open params.key");

    gmp_fprintf(file, "%#0Zx\n", p);
    gmp_fprintf(file, "%#0Zx\n", q);
    gmp_fprintf(file, "%#0Zx\n", g);

    fclose(file);
}

void BigNumGenerator::generateQ() {
    do {
        mpz_urandomb(q, rs, 8);
        mpz_setbit(q, 0);
        mpz_setbit(q, 7);
    } while (!isPrime(q));

    gmp_printf("q = %Zd\n", q);
}

void BigNumGenerator::generateP() {
    do {
        generateQ();
        mpz_mul_ui(p, q, 2);
        mpz_add_ui(p, p, 1);
    } while (!isPrime(p));

    gmp_printf("p = %Zd\n", p);
}

void BigNumGenerator::findMultiplicativeGenerator() {
    do {
        mpz_urandomm(g, rs, p);
    } while (!isMultiplicativeGenerator(g));

    gmp_printf("g = %Zd\n", g);
}

void BigNumGenerator::findCyclicGenerator() {
    mpz_t t;
    mpz_t r;
    mpz_inits(t, r, 0);

    mpz_sub_ui(t, p, 1);
    mpz_div(t, t, q);

    do {
        mpz_urandomm(r, rs, p);
        mpz_powm(g, r, t, p);

    } while (mpz_cmp_ui(g, 1) == 0);

    // gmp_printf("r = %Zd\n", r);
    // gmp_printf("t = %Zd\n", t);
    // gmp_printf("g = %Zd\n", g);

    mpz_clears(t, r, 0);
}

bool BigNumGenerator::isPrime(const mpz_t num) {
    return mpz_probab_prime_p(num, reps) > 0;
}

bool BigNumGenerator::isMultiplicativeGenerator(const mpz_t g) {
    bool isGen;
    mpz_t pSub1;
    mpz_t resPowm;

    mpz_inits(pSub1, resPowm, 0);
    mpz_sub_ui(pSub1, p, 1);
    mpz_powm(resPowm, g, q, p);
    isGen = mpz_cmp_ui(g, 1) > 0 && mpz_cmp(g, pSub1) < 0 && mpz_cmp_ui(resPowm, 1) != 0;

    mpz_clears(pSub1, resPowm, 0);
    return isGen;
};
