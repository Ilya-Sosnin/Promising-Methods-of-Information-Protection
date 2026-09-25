#include "generator/BigNumGenerator.h"
#include <fstream>
#include <random>

BigNumGenerator::BigNumGenerator() : qBits{256}, pBits{1024} {
    std::random_device rd;
    gmp_randinit_default(rs);
    gmp_randseed_ui(rs, rd());
};

BigNumGenerator::~BigNumGenerator() {
    gmp_randclear(rs);
};

void BigNumGenerator::generateMultiplicativeParams(GroupParameters& params) {
    generateP(params.q, params.p);
    findMultiplicativeGenerator(params.q, params.p, params.g);
}

void BigNumGenerator::generateCyclicParams(GroupParameters& params) {
    generateP(params.q, params.p);
    findCyclicGenerator(params.q, params.p, params.g);
}

void BigNumGenerator::generateKey(mpz_t key, mpz_srcptr p) {
    do {
        mpz_urandomm(key, rs, p);
    } while (mpz_cmp_ui(key, 0) == 0);
}

void BigNumGenerator::saveParams(GroupParameters& params) {
    FILE *file = fopen("params.key", "w");

    if (file == nullptr)
        throw std::runtime_error("Cannot open params.key");

    gmp_fprintf(file, "%#0Zx\n", params.p);
    gmp_fprintf(file, "%#0Zx\n", params.q);
    gmp_fprintf(file, "%#0Zx\n", params.g);

    fclose(file);
}

void BigNumGenerator::setParamSizes(unsigned int qSize, unsigned int pSize) {
    qBits = qSize;
    pBits = pSize;
}

void BigNumGenerator::generateQ(mpz_t q) {
    do {
        mpz_urandomb(q, rs, qBits);
        mpz_setbit(q, 0);
        mpz_setbit(q, qBits - 1);
    } while (!isPrime(q));

    // gmp_printf("q = %Zd\n", q);
}

void BigNumGenerator::generateP(mpz_t q, mpz_t p) {
    mpz_t k;
    mpz_init(k);

    do {
        generateQ(q);

        mpz_urandomb(k, rs, pBits - qBits);
        mpz_setbit(k, pBits - qBits - 1);

        mpz_mul(p, k, q);
        mpz_add_ui(p, p, 1);
    } while (!isPrime(p));

    mpz_clear(k);
}

void BigNumGenerator::findMultiplicativeGenerator(mpz_srcptr q, mpz_srcptr p, mpz_t g) {
    do {
        mpz_urandomm(g, rs, p);
    } while (!isMultiplicativeGenerator(q, p, g));

    // gmp_printf("g = %Zd\n", g);
}

void BigNumGenerator::findCyclicGenerator(mpz_srcptr q, mpz_srcptr p, mpz_t g) {
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

bool BigNumGenerator::isMultiplicativeGenerator(mpz_srcptr q, mpz_srcptr p, mpz_srcptr g) {
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
