# Simulador de Semaforo

## Execução
./semsim [Tempo total de simulação] [Frequencia de mudança dos sinais] [Tempo para captura de imagem] ... [Tempo para captura de imagem] <br />
Obs.: Todos os tempos são dados em segundos.
Exemplo: ```./semsim 3600 60 60 3300 200 1800 2400```

## Saidas
### Terminal
No terminal sera mostrado todos os eventos na sua ordem de excuçao com com seu devido tempo e uma breve descrição.
Exemplo:
```
...
Tempo: 00:57:04 | Produz novo carro
                | Carro entrou na pista N1Sul
Tempo: 00:57:04 | Produz novo carro
                | Carro entrou na pista L1Leste
Tempo: 00:57:07 | Carro chegou no final da pista
                | Carro saiu da pista L1Leste
Tempo: 00:57:07 | Carro chegou no final da pista
                | Carro saiu da pista L1Leste
Tempo: 00:57:07 | Carro chegou no final da pista
                | Carro saiu da pista L1Leste
Tempo: 00:57:07 | Carro chegou no final da pista
                | Carro saiu da pista L1Leste
Tempo: 00:57:07 | Carro chegou no final da pista
                | Carro saiu da pista L1Leste
Tempo: 00:57:07 | Carro chegou no final da pista
                | Carro saiu da pista L1Leste
Tempo: 00:57:07 | Carro chegou no final da pista
                | Carro saiu da pista L1Leste
Tempo: 00:57:07 | Produz novo carro
                | Carro entrou na pista O1Leste
Tempo: 00:57:09 | Carro chegou no final da pista
Tempo: 00:57:10 | Carro chegou no final da pista
Tempo: 00:57:12 | Carro chegou no final da pista
Tempo: 00:57:15 | Carro chegou no final da pista
Tempo: 00:57:16 | Carro chegou no final da pista
Tempo: 00:57:16 | Produz novo carro
                | Carro entrou na pista L1Leste
Tempo: 00:57:17 | Carro chegou no final da pista
                | Carro saiu da pista L1Leste
Tempo: 00:57:18 | Produz novo carro
                | Carro entrou na pista O1Leste
...
```
Dica: Como a descrição mostrada no terminal pode ser muito grade é recomendo redirecionar a saida para um arquivo.
Exemplo: ```./semsim 3600 60 60 3300 200 1800 2400 > saida.txt```
#### dado.txt
A simulação ira gerar um arquivo ```dado.txt``` com as imagens dos tempos definos nos argumentos da execução e no ultimo instante
da simulação, além de dados gerais do sistema.
Exemplo:
```
...
Imagem do sistema no tempo: 18000
Pistas Fonte
   O1Leste
       Entraram: 1800
       Sairam: 1786
       Dentro: 14
   N1Sul
       Entraram: 896
       Sairam: 893
       Dentro: 3
   S1Norte
       Entraram: 600
       Sairam: 599
       Dentro: 1
   N2Sul
       Entraram: 903
       Sairam: 899
       Dentro: 4
   S2Norte
       Entraram: 295
       Sairam: 294
       Dentro: 1
   L1Oeste
       Entraram: 1803
       Sairam: 1795
       Dentro: 8

Pistas Sumidouro
   O1Oeste
       Sairam: 482
       Entraram: 486
       Dentro: 4
   N1Norte
       Sairam: 502
       Entraram: 504
       Dentro: 2
   S1Sul
       Sairam: 530
       Entraram: 530
       Dentro: 0
   N2Norte
       Sairam: 1592
       Entraram: 1593
       Dentro: 1
   S2Sul
       Sairam: 1602
       Entraram: 1605
       Dentro: 3
   L1Leste
       Sairam: 1535
       Entraram: 1538
       Dentro: 3

Pistas Centrais
   C1Oeste
       Entraram: 866
       Sairam: 864
       Dentro: 2
   C1Leste
       Entraram: 2622
       Sairam: 2614
       Dentro: 8

------------------------------
Tempo de simulação: 18000s
Frequancia do sinal: 12s

Entraram no sistema: 6297
Sairam do sistema: 6243
Permanecem no sistema: 54
Frequencia de saida: 20.81 Carros/min
```
## Observação
No codigo foi usado funções Lambda e function da biblioteca functional do C++ 11
