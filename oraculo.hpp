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
        Evento eventoAtual = eventos.retiraDoInicio();
        tempoAtual = eventoAtual.time;
        std::cout << "Tempo: " << tempoAtual << " | " << eventoAtual.nome << "\n" ;
        if (eventoAtual > tempoFinal) exit(42);
        eventoAtual.run();
        run();
    }

    unsigned int getTempo() { return tempoAtual; }

private:
    ListaEnc<Evento> eventos;
    unsigned int tempoFinal;
    unsigned int tempoAtual{0};
};

#endif