// Copyright [2016] <Evandro Chagas>
#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP
#include <memory>
/**
 * @brief      Elemento da lista
 *
 * @tparam     T     Dado que o elemento vai guardar
 */
template<typename T>
class Elemento {
 private:
	T info;
	std::shared_ptr<Elemento<T>> next;

 public:
     /**
     * @brief      Construtor do Elemento
     *
     * @param[in]  info  Dado que vai saer guardo
     * @param[in]  next  Proximo elemento, null por padrão
     */
    explicit Elemento(const T& info,
    	std::shared_ptr<Elemento<T>> next = nullptr):
		info{info}, next{next} {}
	/**
	 * @brief      Retorna o proximo elemento em relação oa mesmo
	 *
	 * @return     Proximo elemento
	 */
	std::shared_ptr<Elemento<T>> getProximo() const {
		return next;
	}
	/**
	 * @brief      Pega o dado do elemento
	 *
	 * @return     dado presente no elemento
	 */
	const T& getInfo() const {
		return info;
	}

	/**
	 * @brief      Muda o proximo lemtendo
	 *
	 * @param[in]  next  Proximo elemento a ser considerado
	 */
	void setProximo(std::shared_ptr<Elemento<T>> next) {
		this->next = next;
	}
};

#endif
