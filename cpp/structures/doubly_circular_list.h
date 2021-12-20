//! Copyright [2020] <Gabriel Medeiros Lopes Carneiro>
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions

namespace structures {

    template<typename T>
//! classe DoublyLinkedCircularList
    class DoublyCircularList {
    public:
        //! construtor
        DoublyCircularList();
        //! destrutor
        ~DoublyCircularList();
        //! limpa lista
        void clear();
        //! insere no fim
        void push_back(const T& data);
        //! insere no início
        void push_front(const T& data);
        //! insere na posição
        void insert(const T& data, std::size_t index);
        //! insere em ordem
        void insert_sorted(const T& data);
        //! retira da posição
        T pop(std::size_t index);
        //! retira do fim
        T pop_back();
        //! retira do início
        T pop_front();
        //! retira específico
        void remove(const T& data);
        //! lista vazia
        bool empty() const;
        //! contém
        bool contains(const T& data) const;
        //! acesso a um elemento (checando limites)
        T& at(std::size_t index);
        //! getter constante a um elemento
        const T& at(std::size_t index) const;
        //! posição de um dado
        std::size_t find(const T& data) const;
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

            Node(const T& data, Node* prev, Node* next):
                    data_{data},
                    prev_{prev},
                    next_{next}
            {}

            T& data() {
                return data_;
            }
            const T& data() const {
                return data_;
            }

            Node* prev() {
                return prev_;
            }

            const Node* prev() const {
                return prev_;
            }

            void prev(Node* node) {
                prev_ = node;
            }

            Node* next() {
                return next_;
            }

            const Node* next() const {
                return next_;
            }

            void next(Node* node) {
                next_ = node;
            }

        private:
            T data_;
            Node* prev_{nullptr};
            Node* next_{nullptr};
        };

        Node* head{nullptr};  // primeiro da lista
        Node* tail{nullptr};  // ultimo da lista
        std::size_t size_{0u};
    };

}  // namespace structures

#endif

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T &data) {
    insert(data, size_);
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T &data) {
    Node *novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("lista cheia");
    } else {
        novo->prev(nullptr);
        novo->next(head);
        head = novo;
        if (novo->next() != nullptr) {
            novo->next()->prev(novo);
        }
        size_++;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T &data,
                                               std::size_t index) {
    if (index > size_ || index < 0) {
        throw std::out_of_range("posição inváilida");
    } else {
        Node *novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("lista cheia");
        } else if (index == 0) {
            push_front(data);
        } else {
            auto anterior = head;
            for (int i = 1; i < index; i++) {
                anterior = anterior->next();
            }
            novo->next(anterior->next());
            if (novo->next() != nullptr) {
                novo->next()->prev(novo);
            }
            anterior->next(novo);
            novo->prev(anterior);
            size_++;
        }
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T &data) {
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
T structures::DoublyCircularList<T>::pop(std::size_t index) {
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
        if (eliminar->next() != nullptr) {
            eliminar->next()->prev(anterior);
        }
        size_--;
        delete eliminar;
        return data_aux;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        T data_aux;
        auto saiu = head;
        data_aux = saiu->data();
        head = saiu->next();
        if (head != nullptr) {
            head->prev(nullptr);
        }
        size_--;
        delete saiu;
        return data_aux;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T &data) {
    pop(find(data));
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T &data) const {
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
T & structures::DoublyCircularList<T>::at(std::size_t index) {
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
const T & structures::DoublyCircularList<T>::at(std::size_t index) const {
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
std::size_t structures::DoublyCircularList<T>::find(const T &data) const {
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
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}
