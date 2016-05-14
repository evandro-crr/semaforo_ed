#ifndef CRIANCASCHINESA_HPP
#define CRIANCASCHINESA_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include "oraculo.hpp"
#include "pista.hpp"

class CriancasChinesa {
public:
    CriancasChinesa(Oraculo &O, Pista &P, unsigned int frequencia, unsigned int variacao, std::string saida) :
        oraculo{O}, pista{P}, frequencia{frequencia}, variacao{variacao}, saida{saida} {
            unsigned int tempo = frequencia - variacao + (std::rand() % ((variacao*2)+1));
            oraculo.add(Oraculo::Evento([&]() {add();}, tempo, "Produz primeiros carros"));
    }
    void add() {
        if (pista.add()) std::cout << "                | → → → " << saida << "\n";
        unsigned int tempo = frequencia - variacao + (std::rand() % ((variacao*2)+1));
        oraculo.add(Oraculo::Evento([&]() {add();}, oraculo.getTempo() + tempo, "Produz novo carro"));
    }

private:
    Oraculo &oraculo;
    Pista &pista;
    unsigned int frequencia;
    unsigned int variacao;
    std::string saida;
};

#endif