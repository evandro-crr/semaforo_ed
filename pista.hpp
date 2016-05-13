#ifndef PISTA_HPP
#define PISTA_HPP

#include <cstdlib>
#include <iostream>
#include <functional>
#include "oraculo.hpp"
#include "fila/FilaEnc.hpp"

class Pista {
    struct Carro {
        Carro() {
            tamanho = 2 + (std::rand() % 5) + 3;
        }
        unsigned int tamanho;
        int direcao;
    };

    int probabilidade() {
        int direcao = std::rand() % 101;
        if (direcao <= pDirecao[0]) {
            direcao = 0;
        } else if (direcao <= pDirecao[0]+pDirecao[1]) {
            direcao = 1;
        } else {
            direcao = 2;
        }
        return direcao;
    }

public:
    Pista(Oraculo &O, unsigned int velocidade, unsigned int tamanho, unsigned int posicao,
        int pEsquerda = 0, int pFrente = 0, int pDireita = 0) :
        oraculo{O}, velocidade{velocidade}, tamanho{tamanho}, posicao{posicao} {
            pDirecao[0] = pEsquerda;
            pDirecao[1] = pFrente;
            pDirecao[2] = pDireita;
        }

    bool add() {
        Carro novoCarro = Carro();
        novoCarro.direcao = probabilidade();
        if (tamanhoUsado + novoCarro.tamanho <= tamanho) {
            std::cout << "entrou\n";
            fila.inclui(novoCarro);
            tamanhoUsado += novoCarro.tamanho;
            oraculo.add(Oraculo::Evento([&]() { std::cout << "saiu: " << posicao << "\n"; final(posicao);}, oraculo.getTempo() + (tamanho / 10 * 36 / velocidade), "Remove carro"));
            return true;
        }
        return false;
    }

    bool add(Carro carro) {
        if (tamanhoUsado + carro.tamanho <= tamanho) {
            std::cout << "entrou\n";
            carro.direcao = probabilidade();
            fila.inclui(carro);
            tamanhoUsado += carro.tamanho;
            oraculo.add(Oraculo::Evento([&]() { std::cout << "saiu: " << posicao << "\n"; final(posicao);}, oraculo.getTempo() + (tamanho / 10 * 36 / velocidade), "Remove carro"));
            return true;
        }
        return false;
    }

    void remove() {
        tamanho -= fila.retira().tamanho;
    }

    Carro primeiro() {
        return fila.primeiro();
    }

    bool lock{false};
    std::function<void(int)> final;

private:
    Oraculo &oraculo;
    unsigned int velocidade;
    unsigned int tamanho;
    unsigned int tamanhoUsado{0};
    FilaEnc<Carro> fila;
    unsigned int posicao;
    int pDirecao[3];
};

#endif