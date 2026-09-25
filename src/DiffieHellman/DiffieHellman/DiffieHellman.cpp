#include "DiffieHellman/DiffieHellman.h"

#include <iostream>

DiffieHellman::DiffieHellman() {
    mpz_inits(publicKey, privateKey, peerPublicKey, sharedSecret, nullptr);
}

DiffieHellman::DiffieHellman(const GroupParameters& params) {
    mpz_inits(publicKey, privateKey, peerPublicKey, sharedSecret, nullptr);
    setParams(params);
}

DiffieHellman::~DiffieHellman() {
    mpz_clears(publicKey, privateKey, peerPublicKey, sharedSecret, nullptr);
}

void DiffieHellman::generateParams() {
    gen.generateCyclicParams(params);
}

void DiffieHellman::generateKeys() {
    gen.generateKey(privateKey, params.p);
    mpz_powm(publicKey, params.g, privateKey, params.p);
}

void DiffieHellman::calculateSharedSecret() {
    mpz_powm(sharedSecret, peerPublicKey, privateKey, params.p);
}

void DiffieHellman::setParams(const GroupParameters& newParams) {
    mpz_set(params.q, newParams.q);
    mpz_set(params.p, newParams.p);
    mpz_set(params.g, newParams.g);
}

void DiffieHellman::setPeerPublicKey(mpz_srcptr key) {
    mpz_set(peerPublicKey, key);
}

void DiffieHellman::printParams() {
    gmp_printf("Q: %Zd\n", params.q); 
    gmp_printf("P: %Zd\n", params.p); 
    gmp_printf("G: %Zd\n", params.g); 
}

void DiffieHellman::printKeys() {
    gmp_printf("Public key: %Zd\n", publicKey); 
    gmp_printf("Private key: %Zd\n", privateKey);
}

void DiffieHellman::printPeerPublicKey() {
    gmp_printf("Peer public key: %Zd\n", peerPublicKey); 
}

void DiffieHellman::printSharedSecret() {
    gmp_printf("Shared secreet: %Zd\n", sharedSecret);
}
