#ifndef LIMBO_HPP
#define LIMBO_HPP

#include <iostream>
#include <string>
#include "pista.hpp"

/**
 * @brief      Para onde os carros vão quando saem da simulação.
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
     * @brief      Consome um carro.
     *
     * @param[in]  i     Nada não.
     */
    void run(int i) {
        pista.remove();
        std::cout << "                | → → → " << saida << "\n";
    }

private:
    Pista &pista;
    std::string saida;
};

#endif