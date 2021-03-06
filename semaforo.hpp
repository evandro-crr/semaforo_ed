// Copyright [2016] <Evandro Chagas>
// Copyright [2016] <Lucas Sousa>
#ifndef SEMAFORO_HPP
#define SEMAFORO_HPP

#include "oraculo.hpp"
#include "pista.hpp"

/**
 * @brief      Representação do semaforo.
 */
class Semaforo {
public:

    /**
     * @brief      Construtor. Adiciona o primeiro evento de troca de sinal.
     *
     * @param[in]  pSemaforo   Posição do semaforo.
     * @param      in0         Entrada oeste.
     * @param      in1         Entrada norte.
     * @param      in2         Entrada leste.
     * @param      in3         Entrada sul.
     * @param      out0        Saida oeste.
     * @param      out1        Saida norte.
     * @param      out2        Saida leste.
     * @param      out3        Saida sul.
     * @param      O           Referencia para o oraculo.
     * @param[in]  frequencia  Frequancia de mudança de sinal.
     */
    Semaforo(int pSemaforo, Pista &in0, Pista &in1, Pista &in2, Pista &in3,
            Pista &out0, Pista &out1, Pista &out2, Pista &out3,
            Oraculo &O, unsigned int frequencia) :
            pSemaforo{pSemaforo}, oraculo{O}, frequencia{frequencia} {
                in[0] = &in0;
                in[1] = &in1;
                in[2] = &in2;
                in[3] = &in3;
                out[0] = &out0;
                out[1] = &out1;
                out[2] = &out2;
                out[3] = &out3;
                oraculo.add(Oraculo::Evento([&]() {troca();}, frequencia,
                            "Primeira troca de sinal"));
    }

    /**
     * @brief      Troca o sinal e adiciona o evento da proxima troca de sinal.
     */
    void troca() {
        aberto = (Aberto) (((int) aberto + 1) % (int) max);
        ultimaTroca = oraculo.getTempo();
        oraculo.add(Oraculo::Evento([&]() {troca();},
                    oraculo.getTempo() + frequencia, "Troca de sinal"));
    }

    /**
     * @brief      Passa carro pelo semaforo.
     *
     *             Tenta passar o carro pela sinal, removendo de uma pista e
     *             adicionado na outra, caso não consiga, tranca a pista e
     *             adiciona um novo evento na proxima troca de sinal para
     *             liberar a pista e tentar passar novamente pelo sinal.
     *
     * @param[in]  pposicao  Pista de onde o carro vem.
     */
    void passar(int pposicao) {
        int posicao = pposicao;
        // Trata a entrada casso seja o semaforo 2.
        if (pSemaforo == 2) posicao -= 2;
        // Se o semaforo estiver aberto nessa pista, a rua não estiver trancada
        // e conseguiu passar o carro para seu destino, retira o carro da pista
        // de onde ele vem.
        if ((posicao == (int) aberto) && !(in[posicao]->lock) &&
            out[(posicao + (in[posicao]->primeiro().direcao) + 1) % (int) max]->
                add(in[posicao]->primeiro())) {
            in[posicao]->remove();
        } else {
            in[posicao]->lock = true;
            oraculo.add(Oraculo::Evento([&, posicao, pposicao]() {
                        in[posicao]->lock = false ; passar(pposicao);},
                        ultimaTroca + 1 + frequencia,
                        "Tentando mover carro novamente"));
        }
    }

private:
    int pSemaforo;
    Pista *in[4];
    Pista *out[4];
    Oraculo &oraculo;
    unsigned int frequencia;
    unsigned int ultimaTroca{0};
    enum Aberto { oeste, norte, leste, sul, max } aberto{oeste};

};

#endif