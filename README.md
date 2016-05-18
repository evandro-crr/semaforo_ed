# Simulador de Semaforo

## Execução
./semsim [Tempo total de simulação] [Frequencia de mudança dos sinais] [Tempo para captura de imagem] ... [Tempo para captura de imagem] <br />
Obs.: Todos os tempos são dados em segundos.
Exemplo.
```
./semsim 3600 60 60 3300 200 1800 2400
```

## Saidas
### Terminal
No terminal sera mostrado todos os eventos na sua ordem de excuçao com com seu devido tempo e uma breve descrição.
Exemplo.
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
#### dado.txt
A simulação ira gerar um arquivo ```dado.txt``` com as imagens dos tempos definos nos argumentos da execução e no ultimo instante
da simulação, além de dados gerais do sistema.
Exemplo.
```
...
Imagem do sistema no tempo: 3300
Pista Fonstes
   O1Leste
       Entraram: 331
       Sairam: 310
       Dentro: 21
   N1Sul
       Entraram: 166
       Sairam: 161
       Dentro: 5
   S1Norte
       Entraram: 107
       Sairam: 101
       Dentro: 6
   N2Sul
       Entraram: 168
       Sairam: 163
       Dentro: 5
   S2Norte
       Entraram: 54
       Sairam: 51
       Dentro: 3
   L1Oeste
       Entraram: 323
       Sairam: 319
       Dentro: 4

Pistas Sumidouro
   O1Oeste
       Sairam: 102
       Entraram: 107
       Dentro: 5
   N1Norte
       Sairam: 96
       Entraram: 96
       Dentro: 0
   S1Sul
       Sairam: 95
       Entraram: 95
       Dentro: 0
   N2Norte
       Sairam: 263
       Entraram: 266
       Dentro: 3
   S2Sul
       Sairam: 270
       Entraram: 272
       Dentro: 2
   L1Leste
       Sairam: 257
       Entraram: 257
       Dentro: 0

Pistas Centrais
   C1Oeste
       Entraram: 171
       Sairam: 171
       Dentro: 0
   C1Leste
       Entraram: 445
       Sairam: 433
       Dentro: 12

------------------------------
Imagem do sistema no tempo: 3600
Pista Fonstes
   O1Leste
       Entraram: 362
       Sairam: 334
       Dentro: 28
   N1Sul
       Entraram: 181
       Sairam: 174
       Dentro: 7
   S1Norte
       Entraram: 117
       Sairam: 116
       Dentro: 1
   N2Sul
       Entraram: 184
       Sairam: 175
       Dentro: 9
   S2Norte
       Entraram: 60
       Sairam: 59
       Dentro: 1
   L1Oeste
       Entraram: 354
       Sairam: 343
       Dentro: 11

Pistas Sumidouro
   O1Oeste
       Sairam: 109
       Entraram: 109
       Dentro: 0
   N1Norte
       Sairam: 106
       Entraram: 106
       Dentro: 0
   S1Sul
       Sairam: 98
       Entraram: 98
       Dentro: 0
   N2Norte
       Sairam: 278
       Entraram: 279
       Dentro: 1
   S2Sul
       Sairam: 300
       Entraram: 300
       Dentro: 0
   L1Leste
       Sairam: 284
       Entraram: 284
       Dentro: 0

Pistas Centrais
   C1Oeste
       Entraram: 183
       Sairam: 181
       Dentro: 2
   C1Leste
       Entraram: 492
       Sairam: 469
       Dentro: 23

------------------------------
Tempo de simulação: 3600s
Frequancia do sinal: 60s

Entraram no sistema: 1258
Sairam do sistema: 1175
Permanecem no sistema: 83
Frequencia de saida: 19.5833 Carros/min
```
## Observação
No codigo foi usado funções Lambda e function da biblioteca functional do C++ 11
