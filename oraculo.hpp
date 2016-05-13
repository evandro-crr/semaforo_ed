#ifndef ORACULO_HPP
#define ORACULO_HPP

#include <functional>
#include "lista/ListaEnc.hpp"
class Oraculo {
    struct Evento {
        template <class F>
        Evento(F run, unsigned int time) :
            run{run}, time{time} {}
        std::function<void()> run;
        unsigned int time;
        bool operator>(const Evento &outro) {
            return time > outro.time;
        }
        bool operator>(int outro) {
            return time > outro;
        }
    };
public:
    Oraculo(unsigned int tempoFinal) :
        tempoFinal{tempoFinal} {}

    void add(Evento novoEvento) {
        eventos.adicionaEmOrdem(novoEvento);
    }

    void run() {
        Evento eventoAtual = eventos.retiraDoInicio();
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