#include "DiffieHellman/DiffieHellman.h"
#include <iostream>

int main() {

    DiffieHellman alice;

    alice.generateParams();
    alice.printParams();

    alice.generateKeys();
    alice.printKeys();

    DiffieHellman bob(alice.getParams());
    bob.printParams();

    bob.generateKeys();
    bob.printKeys();

    bob.setPeerPublicKey(alice.getPublicKey());
    alice.printPeerPublicKey();

    alice.setPeerPublicKey(bob.getPublicKey());
    alice.printPeerPublicKey();

    alice.calculateSharedSecret();

    bob.calculateSharedSecret();
    bob.printPeerPublicKey();

    alice.printSharedSecret();
    bob.printSharedSecret();

    return 0;
} 