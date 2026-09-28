#include "DiffieHellman/DiffieHellman.h"
#include "DiffieHellmanSubgroup/DiffieHellmanSubgroup.h"
#include "MQV/MQV.h"

#include <iostream>

void multiplicativeGroupDH() {
    std::cout << "Protocol Diffie-Hellman (Multiplicative group)\n";
    DiffieHellman alice;

    alice.generateParams();

    std::cout << "\nAlice params\n";
    alice.printParams();

    alice.generateKeys();
    std::cout << "\nAlice keys\n";
    alice.printKeys();

    DiffieHellmanSubgroup bob(alice.getParams());
    std::cout << "\nBob params\n";
    bob.printParams();

    bob.generateKeys();
    std::cout << "\nBob keys\n";
    bob.printKeys();

    bob.setPeerPublicKey(alice.getPublicKey());
    alice.setPeerPublicKey(bob.getPublicKey());

    std::cout << "\nAlice peer public key\n";
    alice.printPeerPublicKey();
    std::cout << "\nBob peer public key\n";
    bob.printPeerPublicKey();

    alice.calculateSharedSecret();
    bob.calculateSharedSecret();

    std::cout << "\nAlice share secret\n";
    alice.printSharedSecret();
    std::cout << "\nBob share secret\n";
    bob.printSharedSecret();
}

void cyclicGroupDH() {
    std::cout << "Protocol Diffie-Hellman (Cyclic group)\n";
    DiffieHellmanSubgroup alice;

    alice.generateParams();

    std::cout << "\nAlice params\n";
    alice.printParams();

    alice.generateKeys();
    std::cout << "\nAlice keys\n";
    alice.printKeys();

    DiffieHellmanSubgroup bob(alice.getParams());
    std::cout << "\nBob params\n";
    bob.printParams();

    bob.generateKeys();
    std::cout << "\nBob keys\n";
    bob.printKeys();

    bob.setPeerPublicKey(alice.getPublicKey());
    alice.setPeerPublicKey(bob.getPublicKey());

    std::cout << "\nAlice peer public key\n";
    alice.printPeerPublicKey();
    std::cout << "\nBob peer public key\n";
    bob.printPeerPublicKey();

    alice.calculateSharedSecret();
    bob.calculateSharedSecret();

    std::cout << "\nAlice share secret: \n";
    alice.printSharedSecret();
    std::cout << "\nBob share secret: \n";
    bob.printSharedSecret();
}

void protocolMQV() {
    std::cout << "Protocol MQV\n";
    MQV alice;

    alice.generateParams();

    std::cout << "\nAlice params\n";
    alice.printParams();

    alice.generateKeys();
    std::cout << "\nAlice keys\n";
    alice.printKeys();
    alice.printSessionKeys();

    MQV bob(alice.getParams());
    std::cout << "\nBob params\n";
    bob.printParams();

    bob.generateKeys();
    std::cout << "\nBob keys\n";
    bob.printKeys();
    bob.printSessionKeys();

    bob.setPeerPublicKey(alice.getPublicKey());
    alice.setPeerPublicKey(bob.getPublicKey());

    std::cout << "\nAlice peer public key\n";
    alice.printPeerPublicKey();
    std::cout << "\nBob peer public key\n";
    bob.printPeerPublicKey();

    bob.setPeerSessionPublicKey(alice.getSessionPublicKey());
    alice.setPeerSessionPublicKey(bob.getSessionPublicKey());

    std::cout << "\nAlice peer session public key\n";
    alice.printPeerSessionPublicKey();
    std::cout << "\nBob peer session public key\n";
    bob.printPeerSessionPublicKey();

    alice.calculateSharedSecret(Role::Sender);
    bob.calculateSharedSecret(Role::Receiver);

    std::cout << "\nAlice shared secret\n";
    alice.printSharedSecret();
    std::cout << "\nBob shared secret\n";
    bob.printSharedSecret();
}

int main() {
    multiplicativeGroupDH();
    std::cout << "\n-------------------------------------\n\n";
    cyclicGroupDH();
    std::cout << "\n-------------------------------------\n\n";
    protocolMQV();

    return 0;
} 