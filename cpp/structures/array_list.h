// Copyright [2020] <Gabriel Medeiros Lopes Carneiro>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

    template<typename T>
//! classe ArrayList
    class ArrayList {
    public:
        //! construtor padrao
        ArrayList();
        //! construtor com paremetro
        explicit ArrayList(std::size_t max_size);
        //! destrutor
        ~ArrayList();
        //! metodo limpa a lista
        void clear();
        //! metodo adiciona no final
        void push_back(const T& data);
        //! metodo adiciona no inicio
        void push_front(const T& data);
        //! metodo insere na posicao
        void insert(const T& data, std::size_t index);
        //! metodo insere em ordem
        void insert_sorted(const T& data);
        //! metodo remove da posicao
        T pop(std::size_t index);
        //! metodo remove do final
        T pop_back();
        //! metodo remove do comeco
        T pop_front();
        //! metodo remove dado
        void remove(const T& data);
        //! metodo verifica se esta cheio
        bool full() const;
        //! metodo verifica se esta vazio
        bool empty() const;
        //! metodo verifica se contém dado
        bool contains(const T& data) const;
        //! metodo retorna posição do dado
        std::size_t find(const T& data) const;
        //! metodo retorna tamanho atual
        std::size_t size() const;
        //! metodo retorna tamanho maximo
        std::size_t max_size() const;
        //! metodo retorna dado da posicao index
        T& at(std::size_t index);
        //! metodo retorna dado da posicao index
        T& operator[](std::size_t index);
        //! metodo retorna dado da posicao index
        const T& at(std::size_t index) const;
        //! metodo retorna dado da posicao index
        const T& operator[](std::size_t index) const;

    private:
        T* contents;
        std::size_t size_;
        std::size_t max_size_;

        static const auto DEFAULT_MAX = 10u;
    };

}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    ArrayList<T>(DEFAULT_MAX);
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T &data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        contents[size_] = data;
        size_++;
    }
}

template<typename T>
void structures::ArrayList<T>::push_front(const T &data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else if (empty()) {
        push_back(data);
    } else {
        insert(data, 0);
    }
}

template<typename T>
void structures::ArrayList<T>::insert(const T &data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else if (index < 0 || index > size_) {
        throw std::out_of_range("posiçao inválida");
    } else {
        size_++;
        for (int i = size_ - 1; i > index; i--) {
            contents[i] = contents[i - 1];
        }
        contents[index] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T &data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else if (empty()) {
        push_back(data);
    } else {
        for (int i = 0; i <= size_; i++) {
            if (i == size_) {
                push_back(data);
                break;
            } else if (data < contents[i]) {
                insert(data, i);
                break;
            }
        }
    }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index < 0 || index > size_ - 1) {
        throw std::out_of_range("posiçao inválida");
    } else {
        T aux;
        aux = contents[index];
        for (int i = index; i < size_; i++) {
            contents[i] = contents[i + 1];
        }
        size_--;
        return aux;
    }
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        size_--;
        return contents[size_];
    }
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        return (pop(0));
    }
}

template<typename T>
void structures::ArrayList<T>::remove(const T &data) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        for (int i = 0; i < size_; i++) {
            if (contents[i] == data) {
                pop(i);
            }
        }
    }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return (size_ == max_size_);
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::ArrayList<T>::contains(const T &data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data) {
            return 1;
        }
    }
    return 0;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T &data) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        for (int i = 0; i < size_; i++) {
            if (contents[i] == data) {
                return i;
            }
        }
        return size_;
    }
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T & structures::ArrayList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("posição inválida");
    } else {
        return contents[index];
    }
}

template<typename T>
T & structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T & structures::ArrayList<T>::at(std::size_t index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("posição inválida");
    } else {
        return contents[index];
    }
}

template<typename T>
const T & structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}
