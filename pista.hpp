// Copyright [2016] <Evandro Chagas>
// Copyright [2016] <Lucas Sousa>
#ifndef PISTA_HPP
#define PISTA_HPP

#include <cstdlib>
#include <iostream>
#include <functional>
#include "oraculo.hpp"
#include "fila/FilaEnc.hpp"

/**
 * @brief      Pista por onde os carros passarão.
 */
class Pista {

    /**
     * @brief      Estrutura que representa um carro.
     */
    struct Carro {
        Carro() {
            tamanho = 2 + (std::rand() % 5) + 3;
        }
        unsigned int tamanho;
        int direcao;
    };

    /**
     * @brief      Calcula a direção para qual o carro deve virar de acordo com
     *             as probabilidades da pista.
     *
     * @return     A direção.
     */
    int probabilidade() {
        int direcao = std::rand() % 100;
        if (direcao < pDirecao[0]) {
            direcao = 0;
        } else if (direcao < pDirecao[0]+pDirecao[1]) {
            direcao = 1;
        } else {
            direcao = 2;
        }
        return direcao;
    }

public:

    /**
     * @brief      Construtor
     *
     * @param      O           Referencia para o oraculo.
     * @param[in]  velocidade  Velocidade da pista.
     * @param[in]  tamanho     Tamanho da pista.
     * @param[in]  posicao     Possição da pista em relacao ao semaforo.
     * @param[in]  pEsquerda   Proabilidade de virar a esquerda.
     * @param[in]  pFrente     Proabilidade de siguir em frente.
     * @param[in]  pDireita    Proabilidade de virar a direita.
     */
    Pista(Oraculo &O, unsigned int velocidade, unsigned int tamanho,
          unsigned int posicao, int pEsquerda = 0,
          int pFrente = 0, int pDireita = 0) :
          oraculo{O}, velocidade{velocidade},
          tamanho{tamanho}, posicao{posicao} {
            pDirecao[0] = pEsquerda;
            pDirecao[1] = pFrente;
            pDirecao[2] = pDireita;
    }

    /**
     * @brief      Tenta adicionar um carro novo na pista.
     *
     *             Se houver espço suficiente na pista, adiciona o carro e
     *             agenda um evento de quando ele chegou no final da pista, esse
     *             evento chama a function final.
     *
     * @return     Se conseguiu adicionar o carro.
     */
    bool add() {
        Carro novoCarro = Carro();
        novoCarro.direcao = probabilidade();
        if (tamanhoUsado + novoCarro.tamanho <= tamanho) {
            fila.inclui(novoCarro);
            tamanhoUsado += novoCarro.tamanho;
            ++entrarao;
            oraculo.add(Oraculo::Evento([&]() {final(posicao);},
                        oraculo.getTempo() + (tamanho / 10 * 36 / velocidade),
                        "Carro chegou no final da pista"));
            return true;
        }
        return false;
    }

    /**
     * @brief      Idem ao add porrem recebe o carro que deve ser adicionado.
     *
     * @param[in]  carro  Carro que sera adicioado.
     *
     * @return     Se conseguiu adicionar o carro.
     */
    bool add(Carro carro) {
        if (tamanhoUsado + carro.tamanho <= tamanho) {
            carro.direcao = probabilidade();
            fila.inclui(carro);
            tamanhoUsado += carro.tamanho;
            ++entrarao;
            oraculo.add(Oraculo::Evento([&]() { final(posicao);},
                        oraculo.getTempo() + (tamanho / 10 * 36 / velocidade),
                        "Carro chegou no final da pista"));
            return true;
        }
        return false;
    }

    /**
     * @brief      Remove um carro da pista.
     */
    void remove() {
        tamanhoUsado -= fila.retira().tamanho;
        ++sairam;
    }

    /**
     * @brief      Carro mais a frente na pista.
     *
     * @return     O carro.
     */
    Carro primeiro() {
        return fila.primeiro();
    }

    /**
     * @brief      Quanto carros sairam dessa pista.
     *
     * @return     A quantidade.
     */
    unsigned int quantosSairam() {
        return sairam;
    }

    /**
     * @brief      Quantos carros entraram nessa pista.
     *
     * @return     A quantidade.
     */
    unsigned int quantosEntraram() {
        return entrarao;
    }

    bool lock{false}; //! Se o primeiro carro da pista esta trancando ele.
    std::function<void(int)> final; //! Funçao que sera chamada quando o carro chegar ao final da pista,
                                    //! pode ser tanto o semaforo ou limbo.

private:
    Oraculo &oraculo;
    unsigned int velocidade;
    unsigned int tamanho;
    unsigned int tamanhoUsado{0};
    FilaEnc<Carro> fila;
    unsigned int posicao; // Posiçao relativa ao semaforo 1, onde Oeste = 0, Norte = 1, Leste
                          // = 2, Sul = 3, no semaforo 2 os mesmos valores são utilizado
                          // acresentado 2.
    int pDirecao[3];
    unsigned int entrarao{0};
    unsigned int sairam{0};
};

#endif