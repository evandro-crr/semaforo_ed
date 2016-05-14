#ifndef ORACULO_HPP
#define ORACULO_HPP

#include <functional>
#include <iostream>
#include <string>
#include "lista/ListaEnc.hpp"

class Oraculo {
public:
    struct Evento {
        template <class F>
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

    Oraculo(unsigned int tempoFinal) :
        tempoFinal{tempoFinal} {}

    void add(Evento novoEvento) {
        eventos.adicionaEmOrdem(novoEvento);
    }

    void run() {

        while(true) {
            Evento eventoAtual = eventos.retiraDoInicio();
            tempoAtual = eventoAtual.time;
            if (eventoAtual > tempoFinal) break;
            unsigned int h = tempoAtual / 3600;
            unsigned int m = (tempoAtual / 60) % 60;
            unsigned int s = tempoAtual % 60;

            std::cout << "Tempo: " << (h >= 10 ? "" : "0") << h << ":" << (m >= 10 ? "" : "0") << m << ":" << (s >= 10 ? "" : "0") << s << " | " << eventoAtual.nome << "\n" ;
            eventoAtual.run();
        }
    }

    unsigned int getTempo() { return tempoAtual; }

private:
    ListaEnc<Evento> eventos;
    unsigned int tempoFinal;
    unsigned int tempoAtual{0};
};

#endif