#ifndef DIFFIEHELLMANSUBGROUP_H
#define DIFFIEHELLMANSUBGROUP_H

#include "DiffieHellman/DiffieHellman.h"

class DiffieHellmanSubgroup : public DiffieHellman
{
public:
    DiffieHellmanSubgroup();
    DiffieHellmanSubgroup(const GroupParameters& params);

    void generateParams() override;
    void generateKeys() override;
};

#endif