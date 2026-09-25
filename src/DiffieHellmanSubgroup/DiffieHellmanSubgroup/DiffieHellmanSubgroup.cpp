#include "DiffieHellmanSubgroup/DiffieHellmanSubgroup.h"

DiffieHellmanSubgroup::DiffieHellmanSubgroup() : DiffieHellman() {}

DiffieHellmanSubgroup::DiffieHellmanSubgroup(const GroupParameters& params) : DiffieHellman(params) {}

void DiffieHellmanSubgroup::generateParams() {
    gen.generateCyclicParams(params);
}

void DiffieHellmanSubgroup::generateKeys() {
    gen.generateKey(privateKey, params.q);
    mpz_powm(publicKey, params.g, privateKey, params.p);
}
