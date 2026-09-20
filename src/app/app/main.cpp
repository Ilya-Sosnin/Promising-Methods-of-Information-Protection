#include "generator/BigNumGenerator.h"
#include <iostream>
#include <memory>

int main() {
    BigNumGenerator gen;

    gen.generateParams();
    gen.saveParams();

    return 0;
} 