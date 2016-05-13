#ifndef LIMBO_HPP
#define LIMBO_HPP

#include <iostream>
#include <string>
#include "pista.hpp"

class Limbo {
public:
    Limbo(Pista &pista, std::string saida) :
        pista{pista}, saida{saida} {}

    void run(int i) {
        pista.remove();
        std::cout << saida << std::endl;
    }

private:
    Pista &pista;
    std::string saida;
};

#endif