#ifndef BIGNUMGENERATOR_H
#define BIGNUMGENERATOR_H

#include <gmp.h>

struct GroupParameters
{
    mpz_t p;
    mpz_t q;
    mpz_t g;

    GroupParameters()
    {
        mpz_inits(p, q, g, nullptr);
    }

    ~GroupParameters()
    {
        mpz_clears(p, q, g, nullptr);
    }
};

class BigNumGenerator
{
public:
    BigNumGenerator();
    ~BigNumGenerator();

    void generateMultiplicativeParams(GroupParameters& params);
    void generateCyclicParams(GroupParameters& params);
    void generateKey(mpz_t key, mpz_srcptr p);
    void saveParams(GroupParameters& params);
    void setParamSizes(unsigned int qSize, unsigned int pSize);

private:
    int qBits;
    int pBits;
    static constexpr int reps{30};
    gmp_randstate_t rs;

    void generateQ(mpz_t q);
    void generateP(mpz_t q, mpz_t p);
    void findMultiplicativeGenerator(mpz_srcptr q, mpz_srcptr p, mpz_t g);
    void findCyclicGenerator(mpz_srcptr q, mpz_srcptr p, mpz_t g);

    bool isPrime(const mpz_t num);
    bool isMultiplicativeGenerator(mpz_srcptr q, mpz_srcptr p, mpz_srcptr g);
};

#endif