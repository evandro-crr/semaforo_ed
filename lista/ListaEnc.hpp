// Copyright [2016] <Evandro Chagas>
#include "Elemento.hpp"
/**
 * @brief      Implementação de Lista Encadiada usando Shared Pointer
 *
 * @tparam     T	Tipo de dado guardado pela lista
 */
template<typename T>
class ListaEnc {
 public:
	ListaEnc() {}
	/**
	 * @brief      Posição do dado na lista
	 *
	 * @param[in]  dado  Dado para ser comparado
	 *
	 * @return     Posição em que se encontra do dado
	 */
	int posicao(const T& dado) const {
		if (listaVazia()) throw 20;
		int i = 0;
		auto current = head;
		while (current) {
			if (current->getInfo() == dado) return i;
			current = current->getProximo();
			++i;
		}
		throw 20;
	}
	/**
	 * @brief      Posição do dado na memoria
	 *
	 * @param[in]  dado	 Dado a ser comparado
	 *
	 * @return     Posição de memoria onde o dado esta alocado
	 */
	T* posicaoMem(const T& dado) const {
		if (listaVazia()) throw 20;
		int i = 0;
		auto current = head;
		while (current) {
			if (current->getInfo() == dado) return &(current->getInfo());
			current = current->getProximo();
			++i;
		}
		throw 20;
	}
	/**
	 * @brief      Verifica se a lista comtem do dado
	 *
	 * @param[in]  dado  Dado a ser comparado
	 *
	 * @return     Se o dado esta presente na lista
	 */
	bool contem(const T& dado) const {
		auto current = head;
		while (current) {
			if (current->getInfo() == dado) return true;
			current = current->getProximo();
		}
		return false;
	}
	/**
	 * @brief      Verifica se a lista esta vazia
	 *
	 * @return     Se a lista esta vaszia
	 */
	bool listaVazia() const { return !size; }

	/**
	 * @brief      Adiciona o dado no inicio da lista
	 *
	 * @param[in]  dado	 Dado a ser daicionado
	 */
	void adicionaNoInicio(const T& dado) {
		head = std::make_shared<Elemento<T>>(dado, head);
		++size;
	}
	/**
	 * @brief      Adiciona o dado no final da listta
	 *
	 * @param[in]  dado  Daso a ser adicionado
	 */
	void adiciona(const T& dado) {
		auto novo = std::make_shared<Elemento<T>>(dado);
		if (listaVazia()) {
			head = novo;
		} else {
			auto current = head;
			while (current->getProximo()) {
				current = current->getProximo();
			}
			current->setProximo(novo);
		}
		++size;
	}
	/**
	 * @brief      Adiciona dado em uma posição especifica da lista
	 *
	 * @param[in]  dado  Dado a ser adicionado
	 * @param[in]  pos   Posição onde o dado vai ser adicionado
	 */
	void adicionaNaPosicao(const T& dado, int pos) {
		if (pos < 0 || pos > size) throw 20;
		if (pos == 0) return adicionaNoInicio(dado);
		if (pos == size) return adiciona(dado);
		auto current = head;
		auto old = current;
		while (--pos) {
			old = current;
			current = current->getProximo();
		}
		old->setProximo(std::make_shared<Elemento<T>>(dado, current));
		++size;
	}
	/**
	 * @brief      Adiciona dado de forma que a lista fique ordenada
	 *
	 * @param[in]  dado  Dado a ser adicionado
	 */
	void adicionaEmOrdem(const T& dado) {
		if (listaVazia()) return adicionaNoInicio(dado);
		auto current = head;
		auto old = current;
		int i = 0;
		while (current) {
			if (current->getInfo() > dado) break;
			old = current;
			current = current->getProximo();
			++i;
		}
		if (!i) return adicionaNoInicio(dado);
		if (i == size) return adiciona(dado);
		old->setProximo(std::make_shared<Elemento<T>>(dado, current));
		++size;
	}
	/**
	 * @brief      Remove dado que está no inicio da lista sem retorna-lo
	 */
	void eliminaDoInicio() {
		if (listaVazia()) throw 20;
		head = head->getProximo();
		--size;
	}
	/**
	 * @brief      Remove o dado que está no inicio da lista
	 *
	 * @return     Dado que foi removido
	 */
	T retiraDoInicio() {
		if (listaVazia()) throw 20;
		T retorno = head->getInfo();
		head = head->getProximo();
		--size;
		return retorno;
	}
	/**
	 * @brief      Retira o dado que está no final da lista
	 *
	 * @return     Dado que foi removido
	 */
	T retira() {
		if (listaVazia()) throw 20;
		auto current = head;
		auto old = current;
		while (current->getProximo()) {
			old = current;
			current = current->getProximo();
		}
		T retorno = current->getInfo();
		old->setProximo(nullptr);
		--size;
		return retorno;
	}
	/**
	 * @brief      Remove dado espesifico da lista
	 *
	 * @param[in]  dado	 Dado que vai ser removido
	 *
	 * @return     Dado que removido
	 */
	T retiraEspecifico(const T& dado) {
		if (listaVazia()) throw 20;
		auto current = head;
		auto old = current;
		int i = 1;
		while (current->getProximo()) {
			if (current->getInfo() == dado) break;
			old = current;
			current = current->getProximo();
			++i;
		}
		if (i == size && !(current->getProximo())) throw 20;
		T retorno = current->getInfo();
		old->setProximo(current->getProximo());
		--size;
		return retorno;
	}
	/**
	 * @brief      Retira dado de uma posição espesifica
	 *
	 * @param[in]  pos	Posição do dado que vai ser removido
	 *
	 * @return     Dado que foi removido
	 */
	T retiraDaPosicao(int pos) {
		++pos;
		if (listaVazia()) throw 20;
		if (pos < 0 || pos > size) throw 20;
		if (pos == 0) return retiraDoInicio();
		if (pos == size) return retira();
		auto current = head;
		auto old = current;
		while (--pos) {
			old = current;
			current = current->getProximo();
		}
		T retorno = current->getInfo();
		old->setProximo(current->getProximo());
		--size;
		return retorno;
	}
	/**
	 * @brief      Compara se os dados sao iguais
	 *
	 * @param[in]  dado1  Dado a ser comparado
	 * @param[in]  dado2  Dado a ser comparado
	 *
	 * @return     Se os dados sao maiores
	 */
	bool igual(T dado1, T dado2) { return dado1 == dado2; }
	/**
	 * @brief      Compara se um dado é maior que o outro
	 *
	 * @param[in]  dado1  Primeiro dado a ser comparado
	 * @param[in]  dado2  Segundo dado a ser comparado
	 *
	 * @return     Se o preimeiro dado é maior que o outro
	 */
	bool maior(T dado1, T dado2) { return dado1 > dado2; }
	/**
	 * @brief      Compara se um dado é menor que o outro
	 *
	 * @param[in]  dado1  Primeiro dado a ser comparado
	 * @param[in]  dado2  Segundo dado a ser comparado
	 *
	 * @return     Seo primeiro dado é menor que o outro
	 */
	bool menor(T dado1, T dado2) { return dado1 < dado2; }
	/**
	 * @brief      Remove todos os elementos da lista
	 */
	void destroiLista() {
		head = nullptr;
		size = 0;
	}

 private:
	std::shared_ptr<Elemento<T>> head = nullptr;
	int size = 0;
};
