#include "semaforo.hpp"
#include "limbo.hpp"
#include "produtor.hpp"

int main(int argc, char const *argv[]) {

    if (argc != 3) {
        std::cout << "Duração da simulacao, Frequencia do sinal\n";
        exit(-1);
    }

    unsigned int duracao = std::atoi(argv[1]);
    unsigned int frequencia = std::atoi(argv[2]);

    Oraculo oraculo(duracao);

    // Semaforo 1

    Pista o1oeste(oraculo, 80, 2000, 0);
    Limbo lo1oeste(o1oeste,"Carro saiu da pista O1Oeste");
    o1oeste.final = [&](int i) { lo1oeste.run(i); };
    Pista o1leste(oraculo, 80, 2000, 0, 10, 80, 10);
    Produtor po1leste(oraculo, o1leste, 10, 2, "Carro entrou no pista O1Leste");

    Pista n1norte(oraculo, 60, 500, 1);
    Limbo ln1norte(n1norte, "Carro saiu da pista N1Norte");
    n1norte.final = [&](int i) { ln1norte.run(i); };
    Pista n1sul(oraculo, 60, 500, 1, 80, 10, 10);
    Produtor pn1sul(oraculo, n1sul, 20, 5, "Carro entrou no pista N1Sul");

    Pista c1oeste(oraculo, 60, 300, 2, 30, 40, 30);
    Pista c1leste(oraculo, 60, 300, 2, 30, 40, 30);

    Pista s1sul(oraculo, 60, 500, 3);
    Limbo ls1sul(s1sul, "Carro saiu da pista S1Sul");
    s1sul.final = [&](int i) { ls1sul.run(i); };
    Pista s1norte(oraculo, 60, 500, 3, 10, 10, 80);
    Produtor ps1norte(oraculo, s1norte, 30, 7, "Carro entrou no pista S1Norte");

    // Semaforo 2

    Pista n2norte(oraculo, 40, 500, 3);
    Limbo ln2norte(n2norte, "Carro saiu da pista N2Norte");
    n2norte.final = [&](int i) { ln2norte.run(i); };
    Pista n2sul(oraculo, 40, 500, 3, 40, 30, 30);
    Produtor pn2sul(oraculo, n2sul, 20, 5, "Carro entrou no pista N2sul");

    Pista l1leste(oraculo, 30, 400, 4);
    Limbo ll1leste(l1leste, "Carro saiu da pista L1Leste");
    l1leste.final = [&](int i) { ll1leste.run(i); };
    Pista l1oeste(oraculo, 30, 400, 4, 30, 30, 40);
    Produtor pl1leste(oraculo, l1oeste, 10, 2, "Carro entrou no pista L1Leste");

    Pista s2sul(oraculo, 40, 500, 5);
    Limbo ls2sul(s2sul, "Carro saiu da pista S2Sul");
    s2sul.final = [&](int i) { ls2sul.run(i); };
    Pista s2norte(oraculo, 40, 500, 5, 30, 30, 40);
    Produtor ps2norte(oraculo, s2norte, 60, 15, "Carro entrou no pista S2Norte");

    Semaforo s1(1, o1leste, n1sul, c1oeste, s1norte,
        o1oeste, n1norte, c1leste, s1sul, oraculo, frequencia);

    Semaforo s2(2, c1leste, n2sul, l1oeste, s2norte,
        c1oeste, n2norte, l1leste, s2sul, oraculo, frequencia);

    o1leste.final = [&](int i) { s1.passar(i); };
    n1sul.final = [&](int i) { s1.passar(i); };
    s1norte.final = [&](int i) { s1.passar(i); };
    c1oeste.final = [&](int i) { s1.passar(i); };

    c1leste.final = [&](int i) { s2.passar(i); };
    n2sul.final = [&](int i) { s2.passar(i); };
    s2norte.final = [&](int i) { s2.passar(i); };
    l1oeste.final = [&](int i) { s2.passar(i); };

    oraculo.run();

    return 0;
}