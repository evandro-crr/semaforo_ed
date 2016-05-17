// Copyright [2016] <Evandro Chagas>
// Copyright [2016] <Lucas Sousa>
#ifndef CRIANCASCHINESA_HPP
#define CRIANCASCHINESA_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include "oraculo.hpp"
#include "pista.hpp"

/**
 * @brief      Produz os carros.
 *
 *             Classe que adiciona carros ao sistema pelas pistas produtoras.
 */
class CriancasChinesa {
public:

    /**
     * @brief      Construtor
     *
     * @param[in]  O           Referencia para o oraculo.
     * @param[in]  P           Referencia para a pista.
     * @param[in]  frequencia  Frequenia em que os carros s√£o produzidos.
     * @param[in]  variacao    Varia√ß√£o no tempo da produ√ß√£o.
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
     *
     *             Tenta adicionar um novo carro, e cria um evento baseado na
     *          frequencia e variaÁ„o da pista, ao fim agenda um novo
     *          evento de produÁ„o.
     */
    void produz() {
        if (pista.add())
            std::cout << "                | " << saida << "\n";
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
