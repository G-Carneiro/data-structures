//! Copyright [2020] <Gabriel Medeiros Lopes Carneiro>

#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>

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
        //! altera valor de size
        void set_size(std::size_t size);
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
//-------------------------------------

//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
    class ArrayListString : public ArrayList<char *> {
    public:
        //! construtor padrao
        ArrayListString() : ArrayList() {}
        //! construtor com paremetro
        explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
        //! destrutor
        ~ArrayListString();

        //! metodo limpa a lista
        void clear();
        //! metodo adiciona no final
        void push_back(const char *data);
        //! metodo adiciona no inicio
        void push_front(const char *data);
        //! metodo insere na posicao
        void insert(const char *data, std::size_t index);
        //! metodo insere em ordem
        void insert_sorted(const char *data);
        //! metodo remove da posicao
        char *pop(std::size_t index);
        //! metodo remove do final
        char *pop_back();
        //! metodo remove do comeco
        char *pop_front();
        //! metodo remove dado
        void remove(const char *data);
        //! metodo verifica se contém dado
        bool contains(const char *data);
        //! metodo retorna posição do dado
        std::size_t find(const char *data);
    };

}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    ArrayList(DEFAULT_MAX);
}
template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}
template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    size_ = 0;
    max_size_ = max;
    contents = new T[max_size_];
}
template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}
template<typename T>
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}
template<typename T>
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
void structures::ArrayList<T>::set_size(std::size_t size) {
    size_ = size;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        return contents[index];
    }
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        return contents[index];
    }
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data) {
            return i;
        }
    }
    return size_;
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    if (empty()) return false;
    for (int i = 0; i < size_; i++) {
        if (data == contents[i]) return true;
    }
    return false;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) throw std::out_of_range("lista vazia");
    return contents[--size_];
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size_) {
        throw std::out_of_range("posicao invalida");
    }
    T aux = contents[index];
    for (int i = index; i < size_ - 1; i++) {
        contents[i] = contents[i+1];
    }
    size_--;
    return aux;
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) throw std::out_of_range("lista vazia");
    return pop(0);
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) throw std::out_of_range("lista cheia");
    for (int i = size_; i > 0; i--) {
        contents[i] = contents[i-1];
    }
    contents[0] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        contents[size_++] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else if (index > size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        for (std::size_t i = size_; i > index; i--) {
            contents[i] = contents[i - 1];
        }
        contents[index] = data;
        size_++;
    }
}
// Insert sorted
template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        int cont = size_ - 1;
        while (cont >= 0 && (contents[cont] > data)) {  // !!!
            contents[cont + 1] = contents[cont];
            cont--;
        }
        contents[cont + 1] = data;
        size_++;
    }
}
// Removendo um elemento
template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (!contains(data)) return;
    int i = find(data);
    int j;
    for (j = i; j < size_ - 1; j++) {
        contents[j] = contents[j + 1];
    }
    size_--;
}

structures::ArrayListString::~ArrayListString() {
    for (std::size_t i = 0; i < ArrayList::size(); i++) {
        delete [] ArrayList::operator[](i);
    }
}

void structures::ArrayListString::clear() {
    for (std::size_t i = 0; i < ArrayList::size(); i++) {
        delete [] ArrayList::operator[](i);
    }
    ArrayList::set_size(0);
}

void structures::ArrayListString::insert(const char *data, std::size_t index) {
    if (ArrayList::full()) {
        throw std::out_of_range("Lista cheia.");
    } else {
        char *datanew = new char[strlen(data) + 1];
        snprintf(datanew, strlen(data) + 1, "%s", data);
        datanew[strlen(data)] = '\0';
        ArrayList::insert(datanew, index);
    }
}

void structures::ArrayListString::push_front(const char *data) {
    if (ArrayList::full()) {
        throw std::out_of_range("Lista cheia.");
    } else {
        char *datanew = new char[strlen(data) + 1];
        snprintf(datanew, strlen(data) + 1, "%s", data);
        datanew[strlen(data)] = '\0';
        ArrayList::push_front(datanew);
    }
}

void structures::ArrayListString::push_back(const char *data) {
    if (ArrayList::full()) {
        throw std::out_of_range("Lista cheia.");
    } else {
        char *datanew = new char[strlen(data) + 1];
        snprintf(datanew, strlen(data) + 1, "%s", data);
        datanew[strlen(data)] = '\0';
        ArrayList::push_back(datanew);
    }
}

char * structures::ArrayListString::pop(std::size_t index) {
    if (index >= ArrayList::size()) {
        throw std::out_of_range("posição invalida.");
    } else if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    char *ponto = operator[](index);
    ArrayList::pop(index);
    return ponto;
}

char * structures::ArrayListString::pop_back() {
    char *ponto = this->pop(ArrayList::size()-1);
    return ponto;
}

char * structures::ArrayListString::pop_front() {
    char *ponto = this->pop(0);
    return ponto;
}

bool structures::ArrayListString::contains(const char *data) {
    for (std::size_t i = 0; i < ArrayList::size(); i++) {
        if (!strcmp(ArrayList::at(i), data)) {
            return true;
        }
    }
    return false;
}
// FIND
std::size_t structures::ArrayListString::find(const char *data) {
    for (std::size_t i = 0; i < ArrayList::size(); i++) {
        if (!strcmp(ArrayList::at(i), data)) {
            return i;
        }
    }
    return ArrayList::size();
}

void structures::ArrayListString::insert_sorted(const char *data) {
    int cont = ArrayList::size() - 1;
    while (cont >= 0 && (strcmp(ArrayList::at(cont), data) > 0)) {
        cont--;
    }
    this->insert(data, cont+1);
}

void structures::ArrayListString::remove(const char *data) {
    int pos = this->find(data);
    this->pop(pos);
}
