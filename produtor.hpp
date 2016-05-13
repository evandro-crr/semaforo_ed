#ifndef PRODUTOR_HPP
#define PRODUTOR_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include "oraculo.hpp"
#include "pista.hpp"

class Produtor {
public:
    Produtor(Oraculo &O, Pista &P, unsigned int frequencia, unsigned int variacao, std::string saida) :
        oraculo{O}, pista{P}, frequencia{frequencia}, variacao{variacao}, saida{saida} {
            unsigned int tempo = frequencia - variacao + (std::rand() % ((variacao*2)+1));
            oraculo.add(Oraculo::Evento([&]() {add();}, tempo, "Produz carro"));
    }
    void add() {
        if (pista.add()) std::cout << saida << std::endl;
        unsigned int tempo = frequencia - variacao + (std::rand() % ((variacao*2)+1));
        oraculo.add(Oraculo::Evento([&]() {add();}, oraculo.getTempo() + tempo, "Produz carro"));
    }

private:
    Oraculo &oraculo;
    Pista &pista;
    unsigned int frequencia;
    unsigned int variacao;
    std::string saida;
};

#endif