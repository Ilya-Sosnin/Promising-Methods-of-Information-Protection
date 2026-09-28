#ifndef MQV_H
#define MQV_H

#include "DiffieHellman/DiffieHellman.h"

enum class Role { Sender, Receiver };

class MQV : public DiffieHellman
{
public:
    MQV();
    MQV(const GroupParameters &params);
    ~MQV();
  
    void generateParams() override;
    void generateKeys() override;

    void calculateSharedSecret(Role role);

    void printSessionKeys();
    void printPeerSessionPublicKey();

    mpz_srcptr getSessionPublicKey() const { return publicSessionKey; };
    void setPeerSessionPublicKey(mpz_srcptr key);
    
private:
    mpz_t privateSessionKey;
    mpz_t publicSessionKey;
    mpz_t peerSessionPublicKey; 
};

#endif