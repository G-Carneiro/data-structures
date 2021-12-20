//! Copyright [2020] <Gabriel Medeiros Lopes Carneiro>
#ifndef STRUCTURES_AVL_TREE_H
#define STRUCTURES_AVL_TREE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions
#include "array_list.h"


namespace structures {
    template<typename T>
//! classe AVL TREE
    class AVLTree {
    public:
        //! destrutor
        ~AVLTree();
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
        //! retorna altura
        int height() const;
        //! pre_order
        ArrayList<T> pre_order() const;
        //! in_order
        ArrayList<T> in_order() const;
        //! post_order
        ArrayList<T> post_order() const;
        //! retorna root


    private:
        class Node {
        public:
            explicit Node(const T& data):
                    data_{data}
            {}

            void insert(const T& data_);

            bool remove(const T& data_);

            Node* simpleLeft(Node* k2) {
                auto k1 = k2->left();
                k2->left(k1->right());
                k1->right(k2);

                if (k2->left()->height(k2->left()) >
                    k2->right()->height(k2->right())) {
                    k2->height_ = k2->left()->height(k2->left()) + 1;
                } else {
                    k2->height_ = k2->right()->height(k2->right()) + 1;
                }
                if (k1->left()->height(k1->left()) > k2->height(k2)) {
                    k1->height_ = k1->left()->height(k2->left()) + 1;
                } else {
                    k1->height_ = k2->height(k2) + 1;
                }
                return k1;
            }

            Node* simpleRight(Node* k2) {
                auto k1 = k2->right();
                k2->right(k1->left());
                k1->left(k2);

                if (k2->left()->height(k2->left()) >
                    k2->right()->height(k2->right())) {
                    k2->height_ = k2->left()->height(k2->left()) + 1;
                } else {
                    k2->height_ = k2->right()->height(k2->right()) + 1;
                }
                if (k1->right()->height(k1->right()) > k2->height(k2)) {
                    k1->height_ = k1->right()->height(k1->right()) + 1;
                } else {
                    k1->height_ = k2->height(k2) + 1;
                }
                return k1;
            }

            Node* doubleLeft(Node* k3) {
                k3->left_ = simpleRight(k3->left_);
                return simpleLeft(k3);
            }

            Node* doubleRight(Node* k3) {
                k3->right_ = simpleLeft((k3->right_));
                return simpleRight(k3);
            }

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

            //! retorna altura
            int height(Node* teste) {
                if (teste == nullptr) {
                    return -1;
                }
                return height_;
            }

            void height(int value) {
                height_ = value;
            }

        private:
            T data_;
            int height_{0};
            Node* left_{nullptr};
            Node* right_{nullptr};
        };

        Node* root{nullptr};
        std::size_t size_{0u};
    };

}  // namespace structures

#endif

template<typename T>
structures::AVLTree<T>::~AVLTree<T>() {
    size_ = 0;
}

template<typename T>
int structures::AVLTree<T>::height() const {
    return root->height(root);
}

template<typename T>
void structures::AVLTree<T>::insert(const T &data) {
    Node* new_node = new Node(data);
    structures::ArrayList<T> stack{size_};
    if (empty()) {
        root = new_node;
    } else if (contains(data)) {
        throw std::out_of_range("já está na árvore");
    } else {
        auto aux = root;
        bool flag = true;
        while (flag) {
            // aux->sum_height(1);
            stack.push_back(aux->data());
            if (data < aux->data()) {
                if (aux->left() == nullptr) {
                    aux->left(new_node);
                    new_node->left(nullptr);
                    new_node->right(nullptr);
                    new_node->height(0);
                    flag = false;
                } else {
                    aux = aux->left();
                }
            } else {
                if (aux->right() == nullptr) {
                    aux->right(new_node);
                    new_node->left(nullptr);
                    new_node->right(nullptr);
                    new_node->height(0);
                    flag = false;
                } else {
                    aux = aux->right();
                }
            }
        }
        while (!stack.empty()) {
            Node* ptr = root;
            Node* father = nullptr;
            auto node_data = stack.pop_back();
            while (ptr->data() != node_data) {
                father = ptr;
                if (ptr->data() < node_data) {
                    ptr = ptr->right();
                } else {
                    ptr = ptr->left();
                }
            }
            if ((ptr->left()->height(ptr->left())) -
                ptr->right()->height(ptr->right()) > 1) {
                Node *rotate_tree;
                if (data < ptr->left()->data()) {
                    /*ptr = ptr->left();
                    ptr->right(save);*/
                    rotate_tree = root->simpleLeft(ptr);
                } else {
                    rotate_tree = root->doubleLeft(ptr);
                }
                if (father != nullptr) {
                    if (father->left() == ptr) {
                        father->left(rotate_tree);
                    } else {
                        father->right(rotate_tree);
                    }
                } else {
                    root = rotate_tree;
                }
            } else if ((ptr->right()->height(ptr->right())) -
                       ptr->left()->height(ptr->left()) > 1) {
                Node* rotate_tree;
                if (data > ptr->right()->data()) {
                    /*ptr = ptr->left();
                    ptr->right(save);*/
                    rotate_tree = root->simpleRight(ptr);
                } else {
                    rotate_tree = root->doubleRight(ptr);
                }

                if (father != nullptr) {
                    if (father->right() == ptr) {
                        father->right(rotate_tree);
                    } else {
                        father->left(rotate_tree);
                    }
                } else {
                    root = rotate_tree;
                }
            } else {
                if (ptr->left()->height(ptr->left()) >
                    ptr->right()->height(ptr->right())) {
                    ptr->height(ptr->left()->height(ptr->left()) + 1);
                } else {
                    ptr->height(ptr->right()->height(ptr->right()) + 1);
                }
            }
        }
    }
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T &data) {
    if (empty()) {
        throw std::out_of_range("árvore vazia");
    }
}

template<typename T>
bool structures::AVLTree<T>::contains(const T &data) const {
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
bool structures::AVLTree<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
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
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
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
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
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
