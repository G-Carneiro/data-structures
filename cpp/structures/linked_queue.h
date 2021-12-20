//! Copyright [2020] <Gabriel Medeiros Lopes Carneiro>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions

namespace structures {


    template<typename T>
//! classe LinkedQueue
    class LinkedQueue {
    public:
        //! construtor
        LinkedQueue();
        //! destrutor
        ~LinkedQueue();
        //! limpa fila
        void clear();
        //! enfilerar
        void enqueue(const T& data);
        //! desenfilerar
        T dequeue();
        //! primeiro dado
        T& front() const;
        //! ultimo dado
        T& back() const;
        //! fila vazia
        bool empty() const;
        //! tamanho
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

        Node* head{nullptr};  // nodo-cabeça
        Node* tail{nullptr};  // nodo-fim
        std::size_t size_{0u};  // tamanho
    };

}  // namespace structures

#endif

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (!empty()) {
        dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T &data) {
    Node *novo;
    novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("fila cheia");
    } else {
        if (empty()) {
            head = novo;
        } else {
            tail->next(novo);
        }
        novo->next(nullptr);
        tail = novo;
        size_++;
    }
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        T data_aux;
        auto saiu = head;
        data_aux = saiu->data();
        head = saiu->next();
        if (size_ == 1) {
            tail = nullptr;
        }
        size_--;
        delete saiu;
        return data_aux;
    }
}

template<typename T>
T & structures::LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return head->data();
    }
}

template<typename T>
T & structures::LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return tail->data();
    }
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
