// Copyright [2016] <Evandro Chagas>
// Copyright [2016] <Lucas Sousa>
#include <fstream>
#include <ctime>
#include "semaforo.hpp"
#include "limbo.hpp"
#include "criancas_chinesa.hpp"

Oraculo oraculo;

// Inicialização das pistas

Pista o1oeste(oraculo, 80, 2000, 0); // Cria a pista.
Limbo lo1oeste(o1oeste,"Carro saiu da pista O1Oeste"); // Cria o consumidor da pista acima.
Pista o1leste(oraculo, 80, 2000, 0, 10, 80, 10); // Cria a pista

Pista n1norte(oraculo, 60, 500, 1);
Limbo ln1norte(n1norte, "Carro saiu da pista N1Norte");
Pista n1sul(oraculo, 60, 500, 1, 80, 10, 10);

Pista c1oeste(oraculo, 60, 300, 2, 30, 40, 30);
Pista c1leste(oraculo, 60, 300, 2, 30, 40, 30);

Pista s1sul(oraculo, 60, 500, 3);
Limbo ls1sul(s1sul, "Carro saiu da pista S1Sul");
Pista s1norte(oraculo, 60, 500, 3, 10, 10, 80);

Pista n2norte(oraculo, 40, 500, 3);
Limbo ln2norte(n2norte, "Carro saiu da pista N2Norte");
Pista n2sul(oraculo, 40, 500, 3, 40, 30, 30);

Pista l1leste(oraculo, 30, 400, 4);
Limbo ll1leste(l1leste, "Carro saiu da pista L1Leste");
Pista l1oeste(oraculo, 30, 400, 4, 30, 30, 40);

Pista s2sul(oraculo, 40, 500, 5);
Limbo ls2sul(s2sul, "Carro saiu da pista S2Sul");
Pista s2norte(oraculo, 40, 500, 5, 30, 30, 40);

std::ofstream file;

/**
 * @brief      Gera uma imagem da simulação no memento atual.
 */
void snapshot() {
    file << "Imagem do sistema no tempo: " << oraculo.getTempo() << "\n"
            "Pistas Fonte\n" <<
            "   O1Leste\n" <<
            "       Entraram: " << o1leste.quantosEntraram() << "\n" <<
            "       Sairam: " << o1leste.quantosSairam() << "\n" <<
            "       Dentro: " << o1leste.quantosEntraram() - o1leste.quantosSairam() << "\n" <<
            "   N1Sul\n" <<
            "       Entraram: " << n1sul.quantosEntraram() << "\n" <<
            "       Sairam: " << n1sul.quantosSairam() << "\n" <<
            "       Dentro: " << n1sul.quantosEntraram() - n1sul.quantosSairam() << "\n" <<
            "   S1Norte\n" <<
            "       Entraram: " << s1norte.quantosEntraram() << "\n" <<
            "       Sairam: " << s1norte.quantosSairam() << "\n" <<
            "       Dentro: " << s1norte.quantosEntraram() - s1norte.quantosSairam() << "\n" <<
            "   N2Sul\n" <<
            "       Entraram: " << n2sul.quantosEntraram() << "\n" <<
            "       Sairam: " << n2sul.quantosSairam() << "\n" <<
            "       Dentro: " << n2sul.quantosEntraram() - n2sul.quantosSairam() << "\n" <<
            "   S2Norte\n" <<
            "       Entraram: " << s2norte.quantosEntraram() << "\n" <<
            "       Sairam: " << s2norte.quantosSairam() << "\n" <<
            "       Dentro: " << s2norte.quantosEntraram() - s2norte.quantosSairam() << "\n" <<
            "   L1Oeste\n" <<
            "       Entraram: " << l1oeste.quantosEntraram() << "\n" <<
            "       Sairam: " << l1oeste.quantosSairam() << "\n" <<
            "       Dentro: " << l1oeste.quantosEntraram() - l1oeste.quantosSairam() << "\n\n" <<
            "Pistas Sumidouro\n" <<
            "   O1Oeste\n" <<
            "       Sairam: " << o1oeste.quantosSairam() << "\n" <<
            "       Entraram: " << o1oeste.quantosEntraram() << "\n" <<
            "       Dentro: " << o1oeste.quantosEntraram() - o1oeste.quantosSairam() << "\n" <<
            "   N1Norte\n" <<
            "       Sairam: " << n1norte.quantosSairam() << "\n" <<
            "       Entraram: " << n1norte.quantosEntraram() << "\n" <<
            "       Dentro: " << n1norte.quantosEntraram() - n1norte.quantosSairam() << "\n" <<
            "   S1Sul\n" <<
            "       Sairam: " << s1sul.quantosSairam() << "\n" <<
            "       Entraram: " << s1sul.quantosSairam() << "\n" <<
            "       Dentro: " << s1sul.quantosEntraram() - s1sul.quantosSairam() << "\n" <<
            "   N2Norte\n" <<
            "       Sairam: " << n2norte.quantosSairam() << "\n" <<
            "       Entraram: " << n2norte.quantosEntraram() << "\n" <<
            "       Dentro: " << n2norte.quantosEntraram() - n2norte.quantosSairam() << "\n" <<
            "   S2Sul\n" <<
            "       Sairam: " << s2sul.quantosSairam() << "\n" <<
            "       Entraram: " << s2sul.quantosEntraram() << "\n" <<
            "       Dentro: " << s2sul.quantosEntraram() - s2sul.quantosSairam() << "\n" <<
            "   L1Leste\n" <<
            "       Sairam: " << l1leste.quantosSairam() << "\n" <<
            "       Entraram: " << l1leste.quantosEntraram() << "\n" <<
            "       Dentro: " << l1leste.quantosEntraram() - l1leste.quantosSairam() << "\n\n" <<
            "Pistas Centrais\n" <<
            "   C1Oeste\n" <<
            "       Entraram: " << c1oeste.quantosEntraram() << "\n" <<
            "       Sairam: " << c1oeste.quantosSairam() << "\n" <<
            "       Dentro: " << c1oeste.quantosEntraram() - c1oeste.quantosSairam() << "\n" <<
            "   C1Leste\n" <<
            "       Entraram: " << c1leste.quantosEntraram() << "\n" <<
            "       Sairam: " << c1leste.quantosSairam() << "\n" <<
            "       Dentro: " << c1leste.quantosEntraram() - c1leste.quantosSairam() << "\n" <<
            "\n------------------------------\n";
}

int main(int argc, char const *argv[]) {

    if (argc < 3) {
        std::cout << argv[0] << " [Tempo total de simulação] [Frequencia de mudança dos sinais] [Tempo para captura de imagem] ... [Tempo para captura de imagem]\n";
        exit(-1);
    }

    unsigned int duracao = std::atoi(argv[1]);
    unsigned int frequencia = std::atoi(argv[2]);

    if (!(duracao*frequencia)) {
        std::cout << "Entrada invalida\n";
        exit(-1);
    }

    std::srand(std::time(NULL));
    file.open("dados.txt");

    oraculo = Oraculo(duracao);

    for (int i = 3; i < argc; ++i) {
        unsigned int tempo = std::stoi(argv[i]);
        if (tempo > duracao) {
            std::cout << "Tempo (" << tempo << ") fora da simulação\n";
            exit(-1);
        }
        oraculo.add(Oraculo::Evento([&]() {snapshot();}, tempo,
                    "Imagem da simulação registrada"));
    }
    // Cria produtor para cada pista.

    CriancasChinesa po1leste(oraculo, o1leste, 10, 2,
                             "Carro entrou na pista O1Leste");
    CriancasChinesa pn1sul(oraculo, n1sul, 20, 5,
                           "Carro entrou na pista N1Sul");
    CriancasChinesa ps1norte(oraculo, s1norte, 30, 7,
                             "Carro entrou na pista S1Norte");
    CriancasChinesa pn2sul(oraculo, n2sul, 20, 5,
                           "Carro entrou na pista N2sul");
    CriancasChinesa pl1leste(oraculo, l1oeste, 10, 2,
                             "Carro entrou na pista L1Leste");
    CriancasChinesa ps2norte(oraculo, s2norte, 60, 15,
                             "Carro entrou na pista S2Norte");

    // Liga o final da pista ao seu consumidor.
    o1oeste.final = [&](int i) { lo1oeste.consome(); };
    n1norte.final = [&](int i) { ln1norte.consome(); };
    s1sul.final = [&](int i) { ls1sul.consome(); };
    n2norte.final = [&](int i) { ln2norte.consome(); };
    l1leste.final = [&](int i) { ll1leste.consome(); };
    s2sul.final = [&](int i) { ls2sul.consome(); };

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

    snapshot();
    file << "Tempo de simulação: " << duracao <<"s\n" <<
            "Frequancia do sinal: " << frequencia << "s\n\n" <<
            "Entraram no sistema: " << totalEntrada << "\n" <<
            "Sairam do sistema: " << totalSairam << "\n" <<
            "Permanecem no sistema: " << totalEntrada - totalSairam << "\n" <<
            "Frequencia de saida: " << ((float) totalSairam / ((float) duracao / 60.f)) << " Carros/min\n\n";

    file.close();
    return 0;
}