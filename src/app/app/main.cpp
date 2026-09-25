#include "DiffieHellman/DiffieHellman.h"
#include "DiffieHellmanSubgroup/DiffieHellmanSubgroup.h"

#include <iostream>

void multiplicativeGroupDH() {
    std::cout << "Multiplicative group\n";
    DiffieHellman alice;

 alice.generateParams();

    std::cout << "Alice params: \n";
    alice.printParams();

    alice.generateKeys();
    std::cout << "Alice keys: \n";
    alice.printKeys();

    DiffieHellmanSubgroup bob(alice.getParams());
    std::cout << "Bob params: \n";
    bob.printParams();

    bob.generateKeys();
    std::cout << "Bob keys: \n";
    bob.printKeys();

    bob.setPeerPublicKey(alice.getPublicKey());
    alice.setPeerPublicKey(bob.getPublicKey());

    std::cout << "Alice peer public key: \n";
    alice.printPeerPublicKey();
    std::cout << "Bob peer public key: \n";
    bob.printPeerPublicKey();

    alice.calculateSharedSecret();
    bob.calculateSharedSecret();

    std::cout << "Alice share secret: \n";
    alice.printSharedSecret();
    std::cout << "Bob share secret: \n";
    bob.printSharedSecret();
}

void cyclicGroupDH() {
    std::cout << "Cyclic group\n";
    DiffieHellmanSubgroup alice;

    alice.generateParams();

    std::cout << "Alice params: \n";
    alice.printParams();

    alice.generateKeys();
    std::cout << "Alice keys: \n";
    alice.printKeys();

    DiffieHellmanSubgroup bob(alice.getParams());
    std::cout << "Bob params: \n";
    bob.printParams();

    bob.generateKeys();
    std::cout << "Bob keys: \n";
    bob.printKeys();

    bob.setPeerPublicKey(alice.getPublicKey());
    alice.setPeerPublicKey(bob.getPublicKey());

    std::cout << "Alice peer public key: \n";
    alice.printPeerPublicKey();
    std::cout << "Bob peer public key: \n";
    bob.printPeerPublicKey();

    alice.calculateSharedSecret();
    bob.calculateSharedSecret();

    std::cout << "Alice share secret: \n";
    alice.printSharedSecret();
    std::cout << "Bob share secret: \n";
    bob.printSharedSecret();
}

int main() {
    multiplicativeGroupDH();
    std::cout << "\n-------------------------------------\n\n";
    cyclicGroupDH();

    return 0;
} 