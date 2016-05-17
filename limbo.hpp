// Copyright [2016] <Evandro Chagas>
// Copyright [2016] <Lucas Sousa>
#ifndef LIMBO_HPP
#define LIMBO_HPP

#include <iostream>
#include <string>
#include "pista.hpp"

/**
 * @brief      Para onde os carros vão quando saem da simulação.
 *
 *              Classe que elimina carros do sistema quando estes chegam ao
 *             final de pistas sumidouras.
 */
class Limbo {
public:

    /**
     * @brief      Construtor.
     *
     * @param      pista  Referencia para a psista.
     * @param[in]  saida  Texto de saida no terminal.
     */
    Limbo(Pista &pista, std::string saida) :
        pista{pista}, saida{saida} {}

    /**
     * @brief      Consome um carro da pista.
     */
    void consome() {
        pista.remove();
        std::cout << "                | " << saida << "\n";
    }

private:
    Pista &pista;
    std::string saida;
};

#endif
