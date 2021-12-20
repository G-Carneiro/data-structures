//! Copyright [2020] <Gabriel Medeiros Lopes Carneiro>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions


namespace structures {

//! classe circular list
    template<typename T>
    class CircularList {
    public:
        //! construtor padrão
        CircularList();
        //! destrutor
        ~CircularList();
        //! limpar lista
        void clear();
        //! inserir no fim
        void push_back(const T& data);
        //! inserir no início
        void push_front(const T& data);
        //! inserir na posição
        void insert(const T& data, std::size_t index);
        //! inserir em ordem
        void insert_sorted(const T& data);
        //! acessar um elemento na posição index
        T& at(std::size_t index);
        //! retirar da posição
        T pop(std::size_t index);
        //! retirar do fim
        T pop_back();
        //! retirar do início
        T pop_front();
        //! remover específico
        void remove(const T& data);
        //! lista vazia
        bool empty() const;
        //! contém
        bool contains(const T& data) const;
        //! posição do dado
        std::size_t find(const T& data) const;
        //! tamanho da lista
        std::size_t size() const;

    private:
        class Node {  // Elemento
        public:
            explicit Node(const T& data):
                    data_{data}
            {}

            Node(const T& data, Node* next):
                    data_{data},
                    next_{next}
            {}

            T& data() {  // getter: dado
                return data_;
            }

            const T& data() const {  // getter const: dado
                return data_;
            }

            Node* next() {  // getter: próximo
                return next_;
            }

            const Node* next() const {  // getter const: próximo
                return next_;
            }

            void next(Node* node) {  // setter: próximo
                next_ = node;
            }

        private:
            T data_;
            Node* next_{nullptr};
        };

        Node* end() {  // último nodo da lista
            auto it = head;
            for (auto i = 1u; i < size(); ++i) {
                it = it->next();
            }
            return it;
        }

        Node* head{nullptr};
        std::size_t size_{0u};
    };

}  // namespace structures

#endif


template<typename T>
structures::CircularList<T>::CircularList() {}

template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
}

template<typename T>
void structures::CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::CircularList<T>::push_back(const T &data) {
    insert(data, size_);
}

template<typename T>
void structures::CircularList<T>::push_front(const T &data) {
    Node *novo = new Node(data);
    if (novo == NULL) {
        throw std::out_of_range("lista cheia");
    } else {
        novo->next(head);
        head = novo;
        size_++;
    }
}

template<typename T>
void structures::CircularList<T>::insert(const T &data, std::size_t index) {
    if (index > size_ || index < 0) {
        throw std::out_of_range("posição inválida");
    } else if (index == 0) {
        return push_front(data);
    } else {
        Node *novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("lista cheia");
        } else {
            auto anterior = head;
            for (int i = 1; i < index; i++) {
                anterior = anterior->next();
            }
            novo->next(anterior->next());
            anterior->next(novo);
            size_++;
        }
    }
}

template<typename T>
void structures::CircularList<T>::insert_sorted(const T &data) {
    if (empty()) {
        push_front(data);
    } else {
        auto actual = head;
        int index = 0;
        while (actual->next() != nullptr && data > actual->data()) {
            actual = actual->next();
            index++;
        }
        if (data > actual->data()) {
            insert(data, index + 1);
        } else {
            insert(data, index);
        }
    }
}

template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index >= size_ || index < 0) {
        throw std::out_of_range("posição inválida");
    } else {
        auto actual = head;
        for (int i = 1; i <= index; i++) {
            actual = actual->next();
        }
        return actual->data();
    }
}

template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }

    if (index > size_ - 1 || index < 0) {
        throw std::out_of_range("posição inválida");
    } else if (index == 0) {
        return pop_front();
    } else {
        Node *eliminar;
        T data_aux;
        auto anterior = head;
        for (int i = 1; i < index; i++) {
            anterior = anterior->next();
        }
        eliminar = anterior->next();
        data_aux = eliminar->data();
        anterior->next(eliminar->next());
        size_--;
        delete eliminar;
        return data_aux;
    }
}

template<typename T>
T structures::CircularList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        T data_aux;
        auto saiu = head;
        data_aux = saiu->data();
        head = saiu->next();
        size_--;
        delete saiu;
        return data_aux;
    }
}

template<typename T>
void structures::CircularList<T>::remove(const T &data) {
    pop(find(data));
}

template<typename T>
bool structures::CircularList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::CircularList<T>::contains(const T &data) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        auto actual = head;
        for (int i = 0; i < size_; i++) {
            if (actual->data() == data) {
                return true;
            }
            actual = actual->next();
        }
        return false;
    }
}

template<typename T>
std::size_t structures::CircularList<T>::find(const T &data) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        auto actual = head;
        for (int i = 0; i < size_; i++) {
            if (actual->data() == data) {
                return i;
            }
            actual = actual->next();
        }
        return size_;
    }
}

template<typename T>
std::size_t structures::CircularList<T>::size() const {
    return size_;
}
