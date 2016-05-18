// Copyright [2016] <Evandro Chagas>
// Copyright [2016] <Lucas Sousa>
#ifndef ORACULO_HPP
#define ORACULO_HPP

#include <functional>
#include <iostream>
#include <string>
#include "lista/ListaEnc.hpp"

/**
 * @brief      Gerencia os eventos
 */
class Oraculo {
public:

    /**
     * @brief      Estrutura que guarda o evento.
     */
    struct Evento {
        template <class F>

        /**
         * @brief      Construtor.
         *
         * @param[in]  run   Metodo que sera executado quando o evento for
         *                   chamado.
         * @param[in]  time  Tempo em que esse evento ocorrera.
         * @param[in]  nome  String que sera mostrada quando o eventor for
         *                   executado
         */
        Evento(F run, unsigned int time, std::string nome) :
            run{run}, time{time}, nome{nome} {}
        std::function<void()> run;
        unsigned int time;
        std::string nome;
        bool operator>(const Evento &outro) const {
            return time > outro.time;
        }
        bool operator>(int outro) {
            return time > outro;
        }
    };

    /**
     * @brief      Construtor.
     *
     * @param[in]  tempoFinal  Tempo de duração da simulação.
     */
    Oraculo(unsigned int tempoFinal) :
        tempoFinal{tempoFinal} {}

    Oraculo() {}

    /**
     * @brief      Adiciona evento na lista de evetos.
     *
     * @param[in]  novoEvento  O novo evento.
     */
    void add(Evento novoEvento) {
        eventos.adicionaEmOrdem(novoEvento);
    }

    /**
     * @brief      Executa os evento dentro do tempo de simulação
     */
    void run() {
        while(true) {
            Evento eventoAtual = eventos.retiraDoInicio();
            if (eventoAtual > tempoFinal) break;
            tempoAtual = eventoAtual.time;
            unsigned int h = tempoAtual / 3600;
            unsigned int m = (tempoAtual / 60) % 60;
            unsigned int s = tempoAtual % 60;
            std::cout << "Tempo: " << (h >= 10 ? "" : "0") << h << ":" <<
                         (m >= 10 ? "" : "0") << m << ":" <<
                         (s >= 10 ? "" : "0") << s << " | " <<
                         eventoAtual.nome << "\n" ;
            eventoAtual.run();
        }
    }

    /**
     * @brief      Tempo do ultimo evento executado.
     *
     * @return     O tempo atual.
     */
    unsigned int getTempo() { return tempoAtual; }

private:
    ListaEnc<Evento> eventos;
    unsigned int tempoFinal;
    unsigned int tempoAtual{0};
};

#endif