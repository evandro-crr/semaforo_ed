// Copyright [2016] <Evandro Chagas>
// Copyright [2016] <Lucas Sousa>
#include <fstream>
#include <ctime>
#include "semaforo.hpp"
#include "limbo.hpp"
#include "criancas_chinesa.hpp"

int main(int argc, char const *argv[]) {

    if (argc != 3) {
        std::cout << "<Duração da simulacao> <Frequencia do sinal>\n";
        exit(-1);
    }

    unsigned int duracao = std::atoi(argv[1]);
    unsigned int frequencia = std::atoi(argv[2]);

    if (!(duracao*frequencia)) {
        std::cout << "Entrada invalida\n";
        exit(-1);
    }

    std::srand(std::time(NULL));

    Oraculo oraculo(duracao);

    // Inicialização das pistas

    Pista o1oeste(oraculo, 80, 2000, 0); // Cria a pista.
    Limbo lo1oeste(o1oeste,"Carro saiu da pista O1Oeste"); // Cria o consumidor da pista acima.
    o1oeste.final = [&](int i) { lo1oeste.consome(); }; // Liga o final da pista ao seu consumidor.
    Pista o1leste(oraculo, 80, 2000, 0, 10, 80, 10); // Cria a pista
    CriancasChinesa po1leste(oraculo, o1leste, 10, 2,
                             "Carro entrou na pista O1Leste"); // Cria produtor da pista acima.

    Pista n1norte(oraculo, 60, 500, 1);
    Limbo ln1norte(n1norte, "Carro saiu da pista N1Norte");
    n1norte.final = [&](int i) { ln1norte.consome(); };
    Pista n1sul(oraculo, 60, 500, 1, 80, 10, 10);
    CriancasChinesa pn1sul(oraculo, n1sul, 20, 5,
                           "Carro entrou na pista N1Sul");

    Pista c1oeste(oraculo, 60, 300, 2, 30, 40, 30);
    Pista c1leste(oraculo, 60, 300, 2, 30, 40, 30);

    Pista s1sul(oraculo, 60, 500, 3);
    Limbo ls1sul(s1sul, "Carro saiu da pista S1Sul");
    s1sul.final = [&](int i) { ls1sul.consome(); };
    Pista s1norte(oraculo, 60, 500, 3, 10, 10, 80);
    CriancasChinesa ps1norte(oraculo, s1norte, 30, 7,
                             "Carro entrou na pista S1Norte");

    Pista n2norte(oraculo, 40, 500, 3);
    Limbo ln2norte(n2norte, "Carro saiu da pista N2Norte");
    n2norte.final = [&](int i) { ln2norte.consome(); };
    Pista n2sul(oraculo, 40, 500, 3, 40, 30, 30);
    CriancasChinesa pn2sul(oraculo, n2sul, 20, 5,
                           "Carro entrou na pista N2sul");

    Pista l1leste(oraculo, 30, 400, 4);
    Limbo ll1leste(l1leste, "Carro saiu da pista L1Leste");
    l1leste.final = [&](int i) { ll1leste.consome(); };
    Pista l1oeste(oraculo, 30, 400, 4, 30, 30, 40);
    CriancasChinesa pl1leste(oraculo, l1oeste, 10, 2,
                             "Carro entrou na pista L1Leste");

    Pista s2sul(oraculo, 40, 500, 5);
    Limbo ls2sul(s2sul, "Carro saiu da pista S2Sul");
    s2sul.final = [&](int i) { ls2sul.consome(); };
    Pista s2norte(oraculo, 40, 500, 5, 30, 30, 40);
    CriancasChinesa ps2norte(oraculo, s2norte, 60, 15,
                             "Carro entrou na pista S2Norte");

    // Inicialização dos semaforos.

    Semaforo s1(1, o1leste, n1sul, c1oeste, s1norte,
        o1oeste, n1norte, c1leste, s1sul, oraculo, frequencia);

    Semaforo s2(2, c1leste, n2sul, l1oeste, s2norte,
        c1oeste, n2norte, l1leste, s2sul, oraculo, frequencia);

    // Ligando o final da pista aos semaforos.

    o1leste.final = [&](int i) { s1.passar(i); };
    n1sul.final = [&](int i) { s1.passar(i); };
    s1norte.final = [&](int i) { s1.passar(i); };
    c1oeste.final = [&](int i) { s1.passar(i); };

    c1leste.final = [&](int i) { s2.passar(i); };
    n2sul.final = [&](int i) { s2.passar(i); };
    s2norte.final = [&](int i) { s2.passar(i); };
    l1oeste.final = [&](int i) { s2.passar(i); };

    oraculo.run(); // Inicia a simulação.

    unsigned int totalEntrada{0};
    unsigned int totalSairam{0};

    totalEntrada = o1leste.quantosEntraram() + n1sul.quantosEntraram()
                   + s1norte.quantosEntraram() + n2sul.quantosEntraram()
                   + s2norte.quantosEntraram() + l1oeste.quantosEntraram();

    totalSairam = o1oeste.quantosSairam() + n1norte.quantosSairam()
                  + s1sul.quantosSairam() + n2norte.quantosSairam()
                  + s2sul.quantosSairam() + l1leste.quantosSairam();


    std::ofstream file;
    file.open("dados.txt");

    file << "Tempo de simulação: " << duracao <<
            "s\nFrequancia do sinal: " << frequencia << "s\n\n";

    file << "Entraram no sistema: " << totalEntrada << " Carros\n" <<
            "→ O1Leste : " << o1leste.quantosEntraram() << "\n" <<
            "→ N1Sul   : " << n1sul.quantosEntraram() << "\n" <<
            "→ S1Norte : " << s1norte.quantosEntraram() << "\n" <<
            "→ N2Sul   : " << n2sul.quantosEntraram() << "\n" <<
            "→ S2Norte : " << s2norte.quantosEntraram() << "\n" <<
            "→ L1Oeste : " << l1oeste.quantosEntraram() << "\n\n";

    file << "Sairam do sistema: " << totalSairam << " Carros\n" <<
            "→ O1Oeste : " << o1oeste.quantosSairam() << "\n" <<
            "→ N1Norte : " << n1norte.quantosSairam() << "\n" <<
            "→ S1Sul   : " << s1sul.quantosSairam() << "\n" <<
            "→ N2Norte : " << n2norte.quantosSairam() << "\n" <<
            "→ S2Sul   : " << s2sul.quantosSairam() << "\n" <<
            "→ L1Leste : " << l1leste.quantosSairam() << "\n\n";

    file << "Permanecem no sistema: " << totalEntrada - totalSairam <<
            " Carros\n" << "Frequencia de saida: " <<
            ((float) totalSairam / ((float) duracao / 60.f)) << " Carros/min\n";


    file.close();

    return 0;
}