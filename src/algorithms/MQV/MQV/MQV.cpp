#include "MQV/MQV.h"

#include <iostream>

MQV::MQV() : DiffieHellman() {
    mpz_inits(publicSessionKey, privateSessionKey, peerSessionPublicKey, nullptr);
}

MQV::MQV(const GroupParameters &params) : DiffieHellman(params) {
    mpz_inits(publicSessionKey, privateSessionKey, peerSessionPublicKey, nullptr);
}

MQV::~MQV() {
    mpz_clears(publicSessionKey, privateSessionKey, peerSessionPublicKey, nullptr);
}

void MQV::generateParams() {
    gen.generateCyclicParams(params);
}

void MQV::generateKeys() {
    gen.generateKey(privateKey, params.q);
    mpz_powm(publicKey, params.g, privateKey, params.p);

    gen.generateKey(privateSessionKey, params.q);
    mpz_powm(publicSessionKey, params.g, privateSessionKey, params.p);
}

void MQV::calculateSharedSecret(Role role) {
    unsigned int l;
    mpz_t d;
    mpz_t e;

    mpz_t tmpRes1;
    mpz_t tmpRes2;
    mpz_t tmpRes3;
    mpz_t tmpRes4;

    mpz_inits(d, e, tmpRes1, tmpRes2, tmpRes3, tmpRes4, nullptr);

    l = mpz_sizeinbase(params.q, 2) / 2;

    mpz_t& myParam   = (role == Role::Sender) ? d : e;
    mpz_t& peerParam = (role == Role::Sender) ? e : d;

    mpz_fdiv_r_2exp(myParam, publicSessionKey, l);
    mpz_setbit(myParam, l);

    mpz_fdiv_r_2exp(peerParam, peerSessionPublicKey, l);
    mpz_setbit(peerParam, l);

    mpz_mul(tmpRes1, myParam, privateKey);
    mpz_add(tmpRes2, tmpRes1, privateSessionKey);
    mpz_mod(tmpRes2, tmpRes2, params.q);

    mpz_mod(tmpRes4, peerParam, params.q);
    mpz_powm(tmpRes3, peerPublicKey, tmpRes4, params.p);
    mpz_mul(sharedSecret, peerSessionPublicKey, tmpRes3);
    mpz_powm(sharedSecret, sharedSecret, tmpRes2, params.p);

    mpz_clears(d, e, tmpRes1, tmpRes2, tmpRes3, tmpRes4, nullptr);
}

void MQV::setPeerSessionPublicKey(mpz_srcptr key) {
    mpz_set(peerSessionPublicKey, key);
}

void MQV::printSessionKeys() {
    gmp_printf("Public session key: %Zd\n", publicSessionKey);
    gmp_printf("Private session key: %Zd\n", privateSessionKey);
}
 
void MQV::printPeerSessionPublicKey() {
    gmp_printf("Peer public sesion key: %Zd\n", peerSessionPublicKey); 
}
