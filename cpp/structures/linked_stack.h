//! Copyright [2020] <Gabriel Medeiros Lopes Carneiro>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions

namespace structures {

    template<typename T>
    //! classe LinkedStack
    class LinkedStack {
    public:
        //! construtor
        LinkedStack();
        //! destrutor
        ~LinkedStack();
        //! limpa pilha
        void clear();
        //! empilha
        void push(const T& data);
        //! desempilha
        T pop();
        //! dado no topo
        T& top() const;
        //! pilha vazia
        bool empty() const;
        //! tamanho da pilha
        std::size_t size() const;

    private:
        class Node {  // elemento
        public:
            explicit Node(const T& data):
                    data_{data}
            {}

            Node(const T& data, Node* next):
                    data_{data},
                    next_{next}
            {}

            T& data() {  // getter: info
                return data_;
            }

            const T& data() const {  // getter-constante: info
                return data_;
            }

            Node* next() {  // getter: próximo
                return next_;
            }
            const Node* next() const {  // getter-constante: próximo
                return next_;
            }

            void next(Node* next) {  // setter: próximo
                next_ = next;
            }

        private:
            T data_;
            Node* next_{nullptr};
        };

        Node* top_{nullptr};  // nodo-topo
        std::size_t size_{0u};  // tamanho
    };

}  // namespace structures

#endif

template<typename T>
structures::LinkedStack<T>::LinkedStack() {}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
void structures::LinkedStack<T>::push(const T &data) {
    Node *novo;
    novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("pilha cheia");
    } else {
        novo->next(top_);
        top_ = novo;
        size_++;
    }
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    } else {
        T data_aux;
        auto saiu = top_;
        data_aux = saiu->data();
        top_ = saiu->next();
        size_--;
        delete saiu;
        return data_aux;
    }
}

template<typename T>
T & structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    } else {
        return top_->data();
    }
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
