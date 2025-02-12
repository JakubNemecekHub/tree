#pragma once

#include "bst.hpp"


namespace tree
{

template<typename T>
class AVL : public BST<T>
{
private:

    static void rotate_left_(std::unique_ptr<Node<T>>& node)
    {
        auto temp { node->release_right() };
        node->right(temp->release_left());
        std::swap(node, temp);
        node->left(std::move(temp));
        update_height(node->left());
        update_height(node);;
    }

    static void rotate_right_(std::unique_ptr<Node<T>>& node)
    {
        auto temp { node->release_left() };
        node->left(temp->release_right());
        std::swap(node, temp);
        node->right(std::move(temp));
        update_height(node->right());
        update_height(node);
    }

    static void balance_(std::unique_ptr<Node<T>>& it)
    {
        if ( !it ) return;
        update_height(it);
        switch (skew(it))
        {
        case 2:  // Right heavy
            if ( skew(it->right()) <= -1 ) rotate_right_(it->right());
            rotate_left_(it);
            break;
        case -2:  // Left heavy
            if ( skew(it->left()) >= 1 ) rotate_left_(it->left());
            rotate_right_(it);
        default:
            break;
        }
    }

    void add_(T data, std::unique_ptr<Node<T>>& node) override
    {
        BST<T>::add_(data, node);
        balance_(node);
    }

    T extract_max_(std::unique_ptr<Node<T>>& it) override
    {
        T result { BST<T>::extract_max_(it) };
        balance_(it);
        return result;
    }

    T extract_min_(std::unique_ptr<Node<T>>& it) override
    {
        T result { BST<T>::extract_min_(it) };
        balance_(it);
        return result;
    }

    bool remove_(T key, std::unique_ptr<Node<T>>& it) override
    {
        bool result { BST<T>::remove_(key, it) };
        balance_(it);
        return result;
    }

public:

    AVL() {}
    AVL(Node<T> root) : BST<T>{root} {}
    AVL(T data) : BST<T>(data) {}

};

} // namespace tree

