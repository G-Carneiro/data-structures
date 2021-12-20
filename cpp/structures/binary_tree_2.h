//!  Copyright [2020] <Gabriel Medeiros Lopes Carneiro>

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "./array_list.h"


namespace structures {

//! Classe Árvore binária
    template<typename T>
    class BinaryTree {
    public:
        //! ...
        BinaryTree();
        //! ...
        ~BinaryTree();
        //! ...
        void insert(const T& data);
        //! ...
        void remove(const T& data);
        //! ...
        bool contains(const T& data) const;
        //! ...
        bool empty() const;
        //! ...
        std::size_t size() const;
        //! ...
        ArrayList<T> pre_order() const;
        //! ...
        ArrayList<T> in_order() const;
        //! ...
        ArrayList<T> post_order() const;

        //******************************************************************
        // Prova prática - implementações necessárias:

        // (1) determinação da altura da árvore:
        int height();

        // (2) contagem do número de folhas:
        int leaves();

        // (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
        //     valor da árvore:
        ArrayList<T> limits();

        // (4) criação de uma duplicação, em memória, da árvore:
        BinaryTree<T> clone();

        // (5) remove nós pelo número de seus filhos:
        void filter(int n_child);

        // (6) criação de um nova árvore que tenha todos os valores e a
        //     menor altura possível, ou seja, balanceada com base apenas
        //     no estabelecimento de uma nova ordem de inserção:
        BinaryTree<T> balance();

        void recursive_balance(int middles_list[], int begin, int end,
                               int *pointer_position);

        //******************************************************************


    private:
        struct Node {
            //! Construtor
            explicit Node(const T& data) :
                    data_{data}
            {}

            //! Destrutor
            ~Node() {
                delete left_;
                delete right_;
            }

            T data_;
            Node* left_{nullptr};
            Node* right_{nullptr};

            //! Inserção
            void insert(const T& data) {
                if (data < data_) {
                    if (left_ == nullptr) {
                        left_ = new Node(data);
                        if (left_ == nullptr)
                            throw std::out_of_range("Full tree!");
                    } else {
                        left_->insert(data);
                    }
                } else {
                    if (right_ == nullptr) {
                        right_ = new Node(data);
                        if (right_ == nullptr)
                            throw std::out_of_range("Full tree!");
                    } else {
                        right_->insert(data);
                    }
                }
            }

            //! Remoção
            bool remove(const T& data) {
                bool deleted = false;
                if (data < data_ && left_ != nullptr) {
                    left_ = remove(data, left_, deleted);
                } else if (data > data_ && right_ != nullptr) {
                    right_ = remove(data, right_, deleted);
                } else {
                    if (right_ != nullptr && left_ != nullptr) {
                        Node* temp = right_->minimum();
                        data_ = temp->data_;
                        right_ = remove(data_, right_, deleted);
                    } else if (right_ != nullptr) {
                        Node* temp = right_;
                        data_ = temp->data_;
                        right_ = temp->right_;
                        left_ = temp->left_;
                        temp->right_ = temp->left_ = nullptr;
                        delete temp;
                        deleted = true;
                    } else if (left_ != nullptr) {
                        Node* temp = left_;
                        data_ = temp->data_;
                        right_ = temp->right_;
                        left_ = temp->left_;
                        temp->right_ = temp->left_ = nullptr;
                        delete temp;
                        deleted = true;
                    }
                }
                return deleted;
            }

            //! Contém
            bool contains(const T& data) const {
                if (data < data_)
                    return left_ == nullptr? false : left_->contains(data);
                else if (data > data_)
                    return right_ == nullptr? false : right_->contains(data);
                else
                    return true;
            }

            //! Pré ordem
            void pre_order(ArrayList<T>& v) const {
                v.push_back(data_);
                if (left_ != nullptr)
                    left_->pre_order(v);
                if (right_ != nullptr)
                    right_->pre_order(v);
            }

            //! Em ordem
            void in_order(ArrayList<T>& v) const {
                if (left_ != nullptr)
                    left_->in_order(v);
                v.push_back(data_);
                if (right_ != nullptr)
                    right_->in_order(v);
            }

            //! Pós ordem
            void post_order(ArrayList<T>& v) const {
                if (left_ != nullptr)
                    left_->post_order(v);
                if (right_ != nullptr)
                    right_->post_order(v);
                v.push_back(data_);
            }

            int height() {
                if (this == nullptr) {
                    return -1;
                }
                int left = left_->height();
                int right = right_->height();
                if (left > right) {
                    return left + 1;
                } else {
                    return right + 1;
                }
            }


        private:
            //! Complemento da funcão de remoção
            Node* remove(const T& data, Node* arv, bool& deleted) {
                deleted = false;
                if (arv == nullptr)
                    return arv;
                if (data < arv->data_) {
                    arv->left_ = remove(data, arv->left_, deleted);
                    return arv;
                }
                if (data > arv->data_) {
                    arv->right_ = remove(data, arv->right_, deleted);
                    return arv;
                }
                // doi filhos
                if (arv->right_ != nullptr && arv->left_ != nullptr) {
                    Node* temp = arv->right_->minimum();
                    arv->data_ = temp->data_;
                    arv->right_ = remove(data, arv->right_, deleted);
                    return arv;
                }
                // um filho ou folha
                Node* temp = nullptr;
                if (arv->right_ != nullptr)
                    temp = arv->right_;
                else
                    temp = arv->left_;

                arv->right_ = arv->left_ = nullptr;
                delete arv;
                deleted = true;
                return temp;
            }

            //! Encontrar o menor
            Node* minimum() {
                if (left_ == nullptr)
                    return this;
                return left_->minimum();
            }
        };

        Node* root_{nullptr};
        std::size_t size_{0};
    };




//******************************************************************
// Prova prática - implementações necessárias:

//! (1) determinação da altura da árvore:
    template<typename T>
    int BinaryTree<T>::height() {
        return root_->height();
    }

//! (2) contagem do número de folhas:
    template<typename T>
    int BinaryTree<T>::leaves() {
        ArrayList<T> aux = in_order();
        Node* leave_search;
        T data;
        int num_leaves = 0;
        while (!aux.empty()) {
            leave_search = root_;
            data = aux.pop_front();
            while (leave_search->data_ != data) {
                if (leave_search->data_ < data) {
                    leave_search = leave_search->right_;
                } else {
                    leave_search = leave_search->left_;
                }
            }
            if (leave_search->left_ == nullptr && leave_search->right_ == nullptr) {
                num_leaves++;
            }
        }

        return num_leaves;
    }

//! (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
//!     valor da árvore:
    template<typename T>
    ArrayList<T> BinaryTree<T>::limits() {
        ArrayList<T> L(2);
        Node* aux = root_;
        while (aux->left_ != nullptr) {
            aux = aux->left_;
        }
        L.push_back(aux->data_);

        aux = root_;
        while (aux->right_ != nullptr) {
            aux = aux->right_;
        }
        L.push_back(aux->data_);

        return L;
    }

//! (4) criação de uma duplicação, em memória, da árvore:
    template<typename T>
    BinaryTree<T> BinaryTree<T>::clone() {
        BinaryTree<T> C;
        ArrayList<T> aux = pre_order();

        for (int i = 0; i < aux.size(); i++) {
            C.insert(aux[i]);
        }

        return C;
    }

//! (5) remove nós pelo número de seus filhos:
    template<typename T>
    void BinaryTree<T>::filter(int n_child) {
        ArrayList<T> aux = post_order();
        ArrayList<T> pos{aux.size()};
        Node* ptr;
        T data;
        // aux = post_order();
        while (!aux.empty()) {
            ptr = root_;
            data = aux.pop_front();
            while (ptr->data_ != data) {
                if (ptr->data_ < data) {
                    ptr = ptr->right_;
                } else {
                    ptr = ptr->left_;
                }
            }
            switch (n_child) {
                case 0:
                    if (ptr->left_ == nullptr && ptr->right_ == nullptr) {
                        // remove(data);
                        pos.push_back(data);
                    }
                    break;
                case 1:
                    if ((ptr->left_ == nullptr && ptr->right_ != nullptr) ||
                        (ptr->left_ != nullptr && ptr->right_ == nullptr)) {
                        // remove(data);
                        pos.push_back(data);
                    }
                    break;
                case 2:
                    if (ptr->left_ != nullptr && ptr->right_ != nullptr) {
                        // remove(data);
                        pos.push_back(data);
                    }
                    break;
                default:
                    break;
            }
        }
        while (!pos.empty()) {
            remove(pos.pop_front());
        }
    }

//! (6) criação de um nova árvore que tenha todos os valores e a
//!     menor altura possível, ou seja, balanceada com base apenas
//!     no estabelecimento de uma nova ordem de inserção:
    template<typename T>
    BinaryTree<T> BinaryTree<T>::balance() {
        BinaryTree<T> B;
        ArrayList<T> aux = in_order();
        int position = 0;
        int *pointer_position = &position;
        int middles_list[size_];
        /*for (int i = 0; i < size_; i++) {
            middles_list[i] = 0;
        }*/
        recursive_balance(middles_list, 0, size_ - 1, pointer_position);

        for (int i = 0; i < size_; i++) {
            B.insert(aux[middles_list[i]]);
        }

        return B;
    }
    template<typename T>
    void BinaryTree<T>::recursive_balance(int middles_list[], int begin, int end, int *pointer_position) {
        if (begin <= end) {
            // ArrayList<T> aux = in_order();
            int middle = (begin + end) / 2;
            middles_list[*pointer_position] = middle;
            *pointer_position += 1;
            recursive_balance(middles_list, begin, middle - 1, pointer_position);
            recursive_balance(middles_list, middle + 1, end, pointer_position);
        }
    }

//******************************************************************



//! Construtor
    template<typename T>
    BinaryTree<T>::BinaryTree()
    {}

//! Destrutor
    template<typename T>
    BinaryTree<T>::~BinaryTree() {
        delete root_;
    }

//! Inserção
    template<typename T>
    void BinaryTree<T>::insert(const T& data) {
        if (empty()) {
            root_ = new Node(data);
            if (root_ == nullptr)
                throw std::out_of_range("FUll tree!");
        } else {
            root_->insert(data);
        }
        ++size_;
    }

// Remoção
    template<typename T>
    void BinaryTree<T>::remove(const T& data) {
        if (empty())
            throw std::out_of_range("Empty tree");

        if (size() != 1u) {
            if (root_->remove(data))
                --size_;
        } else {
            if (root_->data_ == data) {
                delete root_;
                root_ = nullptr;
                --size_;
            }
        }
    }

//! Contém
    template<typename T>
    bool BinaryTree<T>::contains(const T& data) const {
        if (empty())
            return false;
        return root_->contains(data);
    }

//! Vazio
    template<typename T>
    bool BinaryTree<T>::empty() const {
        return size() == 0;
    }

//! Tamanho
    template<typename T>
    std::size_t BinaryTree<T>::size() const {
        return size_;
    }

//! Pré ordem
    template<typename T>
    ArrayList<T> BinaryTree<T>::pre_order() const {
        ArrayList<T> v{size_};
        if (!empty())
            root_->pre_order(v);
        return v;
    }

//! Em ordem
    template<typename T>
    ArrayList<T> BinaryTree<T>::in_order() const {
        ArrayList<T> v{size_};
        if (!empty())
            root_->in_order(v);
        return v;
    }

//! Pós ordem
    template<typename T>
    ArrayList<T> BinaryTree<T>::post_order() const {
        ArrayList<T> v{size_};
        if (!empty())
            root_->post_order(v);
        return v;
    }

}  // namespace structures

#endif
