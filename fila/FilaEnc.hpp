// Copyright [2016] <Evandro Chagas>
#include "Elemento.hpp"
template <typename T>
class FilaEnc {
 public:
    FilaEnc<T>() {}
    ~FilaEnc() {}
    /**
     * @brief      Verifica se a fila esta vazia
     *
     * @return     Se a fila esta vazia
     */
    bool filaVazia() { return size == 0; }
    /**
     * @brief      Adiciona um dado no final da fila
     *
     * @param[in]  dado  Dado a ser adicionado
     */
    void inclui(const T& dado) {
        if (filaVazia()) {
            head = std::make_shared<Elemento<T>>(dado, tail);
            tail = head;
        } else if (size == 1) {
            tail = std::make_shared<Elemento<T>>(dado);
            head->setProximo(tail);
        } else {
            auto novo = std::make_shared<Elemento<T>>(dado);
            tail->setProximo(novo);
            tail = novo;
        }
        ++size;
    }
    /**
     * @brief      Retira dado do inicio da fila
     *
     * @return     dado a ser retirado
     */
    T retira() {
        if (filaVazia()) throw 20;
        T retorno = head->getInfo();
        head = head->getProximo();
        --size;
        return retorno;
    }
    /**
     * @brief      Verifica ultimo dado da fila
     *
     * @return     ultimo dado da fila
     */
    T ultimo()  {
        if (filaVazia()) throw 20;
        return tail->getInfo();
    }
    /**
     * @brief      Verifica primeiro dado da fila
     *
     * @return     Primeiro dado da fila
     */
    T primeiro() {
        if (filaVazia()) throw 20;
        return head->getInfo();
    }
    /**
     * @brief      Esvazia a fila
     */
    void limparFila() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

 private:
    std::shared_ptr<Elemento<T>>  head;
    std::shared_ptr<Elemento<T>>  tail;
    int size{0};
};
