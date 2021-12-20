//! Copyright [2020] <Gabriel Medeiros Lopes Carneiro>
#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions
#include "array_list.h"

namespace structures {

    template<typename T>
//! class BinaryTree
    class BinaryTree {
    public:
        //! destrutor
        ~BinaryTree();
        //! inserção de dado
        void insert(const T& data);
        //! remove dado
        void remove(const T& data);
        //! verifica se dado existe
        bool contains(const T& data) const;
        //! verifica se vazio
        bool empty() const;
        //! retorna tamanho
        std::size_t size() const;
        //! pre_order
        ArrayList<T> pre_order() const;
        //! in_order
        ArrayList<T> in_order() const;
        //! post_order
        ArrayList<T> post_order() const;

    private:
        class Node {
        public:
            explicit Node(const T& data):
                    data_{data}
            {}

            void insert(const T& data_);

            bool remove(const T& data_);

            bool contains(const T& data_) const;

            void pre_order(ArrayList<T>& v) const;

            void in_order(ArrayList<T>& v) const;

            void post_order(ArrayList<T>& v) const;
            //! Retorna o dado armazenado.
            T& data() {
                return data_;
            }

            //! Retorna o dado armazenado.
            const T& data() const {
                return data_;
            }

            //! Retorna ponteiro para próximo nodo.
            Node* left() {  // getter: próximo
                return left_;
            }

            //! Retorna ponteiro para o o próximo node.
            const Node* left() const {  // getter const: próximo
                return left_;
            }

            //! Altera o ponteiro para o próximo.
            void left(Node* node) {  // setter: próximo
                left_ = node;
            }
            //! Retorna ponteiro para próximo nodo.
            Node* right() {  // getter: próximo
                return right_;
            }

            //! Retorna ponteiro para o o próximo node.
            const Node* right() const {  // getter const: próximo
                return right_;
            }

            //! Altera o ponteiro para o próximo.
            void right(Node* node) {  // setter: próximo
                right_ = node;
            }

        private:
            T data_;
            Node* left_{nullptr};
            Node* right_{nullptr};
        };

        Node* root{nullptr};
        std::size_t size_{0u};
    };

}  // namespace structures

#endif

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    size_ = 0;
}

template<typename T>
void structures::BinaryTree<T>::insert(const T &data) {
    Node* new_node = new Node(data);
    if (empty()) {
        root = new_node;
    } else if (contains(data)) {
        throw std::out_of_range("elemento já esta na árvore");
    } else {
        auto aux = root;
        bool flag = true;
        while (flag) {
            if (data < aux->data()) {
                if (aux->left() == nullptr) {
                    aux->left(new_node);
                    new_node->left(nullptr);
                    new_node->right(nullptr);
                    flag = false;
                } else {
                    aux = aux->left();
                }
            } else {
                if (aux->right() == nullptr) {
                    aux->right(new_node);
                    new_node->left(nullptr);
                    new_node->right(nullptr);
                    flag = false;
                } else {
                    aux = aux->right();
                }
            }
        }
    }
    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T &data) {
    if (empty()) {
        throw std::out_of_range("árvore vazia");
    } else if (!contains(data)) {
        throw std::out_of_range("dado não existe");
    } else {
        auto excluir = root;
        while (excluir->data() != data) {
            if (data < excluir->data()) {
                excluir = excluir->left();
            } else {
                excluir = excluir->right();
            }
        }
        auto filho = excluir;
        if (excluir->left() != nullptr && excluir->right() != nullptr) {
            filho = excluir->right();
            while (filho->left() != nullptr) {
                filho = filho->left();
            }
            excluir->data() = filho->data();
            if (filho->right() != nullptr) {
                filho->data() = filho->right()->data();
                filho->right(filho->right()->right());
            }
        } else if (excluir->right() != nullptr) {
            excluir->data() = excluir->right()->data();
            excluir->right(excluir->right()->right());
        } else if (excluir->left() != nullptr) {
            excluir->data() = excluir->left()->data();
            excluir->left(excluir->left()->left());
        } else {
            delete excluir;
        }
    }
    size_--;
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T &data) const {
    if (empty()) {
        throw std::out_of_range("árvore vazia");
    } else {
        auto ptr = root;
        while (ptr != nullptr && ptr->data() != data) {
            if (ptr->data() < data) {
                ptr = ptr->right();
            } else {
                ptr = ptr->left();
            }
        }
        return ptr;
    }
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> teste{size_};
    structures::ArrayList<T> help{size_};
    teste.push_back(root->data());
    help.push_back(root->right()->data());
    help.push_back(root->left()->data());
    // testar utilizar pilha!!!

    while (!help.empty()) {
        auto ptr = root;
        auto data = help.pop_back();
        teste.push_back(data);
        while (ptr != nullptr && ptr->data() != data) {
            if (ptr->data() < data) {
                ptr = ptr->right();
            } else {
                ptr = ptr->left();
            }
        }
        if (ptr->right() != nullptr) {
            help.push_back(ptr->right()->data());
        }
        if (ptr->left() != nullptr) {
            help.push_back(ptr->left()->data());
        }
    }
    return teste;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> teste{size_};
    structures::ArrayList<T> help{size_};
    help.push_back(root->right()->data());
    help.push_back(root->data());
    help.push_back(root->left()->data());
    // testar utilizar pilha!!!

    while (!help.empty()) {
        auto ptr = root;
        auto data = help.pop_back();
        while (ptr != nullptr && ptr->data() != data) {
            if (ptr->data() < data) {
                ptr = ptr->right();
            } else {
                ptr = ptr->left();
            }
        }

        if (ptr->right() != nullptr && !help.contains(ptr->right()->data())) {
            help.push_back(ptr->right()->data());
        }
        if (ptr->left() == nullptr || teste.contains(ptr->left()->data())) {
            teste.push_back(ptr->data());
        } else if (ptr->left() != nullptr) {
            help.push_back(ptr->data());
            help.push_back(ptr->left()->data());
        }
    }

    return teste;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    structures::ArrayList<T> teste{size_};
    structures::ArrayList<T> help{size_};
    help.push_back(root->data());
    help.push_back(root->right()->data());
    help.push_back(root->left()->data());
    // testar utilizar pilha!!!

    while (!help.empty()) {
        auto ptr = root;
        auto data = help.pop_back();
        while (ptr != nullptr && ptr->data() != data) {
            if (ptr->data() < data) {
                ptr = ptr->right();
            } else {
                ptr = ptr->left();
            }
        }
        if ((ptr->left() == nullptr || teste.contains(ptr->left()->data())) &&
            (ptr->right() == nullptr || teste.contains(ptr->right()->data()))) {
            teste.push_back(ptr->data());
        } else {
            help.push_back(ptr->data());
        }

        if (ptr->right() != nullptr && !teste.contains(ptr->right()->data())) {
            help.push_back(ptr->right()->data());
        }
        if (ptr->left() != nullptr && !teste.contains(ptr->left()->data())) {
            help.push_back(ptr->left()->data());
        }
    }

    return teste;
}
