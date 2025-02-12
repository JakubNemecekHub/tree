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
        update_depth(node->left());
        update_depth(node);;
    }

    static void rotate_right_(std::unique_ptr<Node<T>>& node)
    {
        auto temp { node->release_left() };
        node->left(temp->release_right());
        std::swap(node, temp);
        node->right(std::move(temp));
        update_depth(node->right());
        update_depth(node);
    }

    static void balance_(std::unique_ptr<Node<T>>& it)
    {
        if ( !it ) return;
        // We are not directly interested in node's depth/height. What is of interest and use to us
        // is the Balance factor of a node.
        // Balance factor (BF) is the difference in height/depth of node's right child ath its left child.
        // When BF ∈ {-1, 0, 1} we say that node is balanced. Otherwise the node is unbalanced and
        // a appropriate rotation operation needs to be performed to balance our poor node.
        // If BF < 0 node is left heavy
        // If BF > 0 node is right heavy
        //
        // Other name for Balance factor is Skew. Unbalanced nodes are said to be skewed. Balanced node are still
        // referred to as balanced.
        //
        update_depth(it);
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

