#ifndef CRIANCASCHINESA_HPP
#define CRIANCASCHINESA_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include "oraculo.hpp"
#include "pista.hpp"

/**
 * @brief      Produz os carros.
 */
class CriancasChinesa {
public:

    /**
     * @brief      Construtor
     *
     * @param      O           Referencia para o oraculo.
     * @param      P           Referencia para a pista.
     * @param[in]  frequencia  Frequenia em que os carros são produzidos.
     * @param[in]  variacao    Variação no tempo da produção.
     * @param[in]  saida       Texto de saida no terminal.
     */
    CriancasChinesa(Oraculo &O, Pista &P, unsigned int frequencia,
                    unsigned int variacao, std::string saida) :
                    oraculo{O}, pista{P}, frequencia{frequencia},
                    variacao{variacao}, saida{saida} {
                        unsigned int tempo = frequencia - variacao +
                                             (std::rand() % ((variacao*2)+1));
                        oraculo.add(Oraculo::Evento([&]() {produz();}, tempo,
                                    "Produz primeiros carros"));
    }

    /**
     * @brief      Produz um carro novo.
     */
    void produz() {
        if (pista.add())
            std::cout << "                | → → → " << saida << "\n";
        unsigned int tempo = frequencia - variacao +
                             (std::rand() % ((variacao*2)+1));
        oraculo.add(Oraculo::Evento([&]() {produz();}, oraculo.getTempo() + tempo,
                    "Produz novo carro"));
    }

private:
    Oraculo &oraculo;
    Pista &pista;
    unsigned int frequencia;
    unsigned int variacao;
    std::string saida;
};

#endif