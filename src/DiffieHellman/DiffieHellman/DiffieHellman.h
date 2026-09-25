#ifndef DIFFIEHELLMAN_H
#define DIFFIEHELLMAN_H

#include "generator/BigNumGenerator.h"

#include <memory>

class DiffieHellman
{
public:
    DiffieHellman();
    DiffieHellman(const GroupParameters& params);
    ~DiffieHellman();

    void generateParams();
    void generateKeys();

    void calculateSharedSecret();

    void setParams(const GroupParameters& newParams);
    void setPeerPublicKey(mpz_srcptr key);

    void printParams();
    void printKeys();
    void printPeerPublicKey();
    void printSharedSecret();

    const GroupParameters& getParams() const { return params; };
    mpz_srcptr getPublicKey() const { return  publicKey; };

private:
    mpz_t publicKey;
    mpz_t privateKey;
    mpz_t peerPublicKey;
    mpz_t sharedSecret;

    GroupParameters params;
    BigNumGenerator gen;
};

#endif