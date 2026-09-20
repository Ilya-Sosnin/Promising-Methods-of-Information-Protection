#ifndef BIGNUMGENERATOR_H
#define BIGNUMGENERATOR_H

#include "gmp.h"

class BigNumGenerator
{
public:
    BigNumGenerator();
    ~BigNumGenerator();

    void generateParams();
    void saveParams();

private:
    static constexpr int reps{30};
    mpz_t q;
    mpz_t p;
    mpz_t g;

    gmp_randstate_t rs;

    void generateQ();
    void generateP();
    void findMultiplicativeGenerator();
    void findCyclicGenerator();

    bool isPrime(const mpz_t num);
    bool isMultiplicativeGenerator(const mpz_t g);
};

#endif