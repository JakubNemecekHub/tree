#pragma once

#include <memory>
#include <algorithm>

#include "linked.hpp"

namespace tree
{

template<typename T>
class AVL
{
private:

    std::unique_ptr<Node<T>> root_ { nullptr };

    // Recursive helper member function for adding nodes.
    void add_(T data, std::unique_ptr<Node<T>>& node)
    {
        if ( data <= node->data )
        {
            if ( !node->left() ) node->left(data);
            else                 add_(data, node->left());
        }
        else
        {
            if ( !node->right() ) node->right(data);
            else                  add_(data, node->right());
        }
        balance_(node);
    }

    static void rotate_left_(std::unique_ptr<Node<T>>& node)
    {
        // node is x
        // TO DO: come up with better name than y
        auto y { node->release_right() };
        node->right(y->release_left());
        std::swap(node, y);
        node->left(std::move(y));
        update_depth(node->left());
        update_depth(node);;
    }

    static void rotate_right_(std::unique_ptr<Node<T>>& node)
    {
        // node is now y
        // TO DO: come up with better name than x
        auto x { node->release_left() };
        node->left(x->release_right());
        std::swap(node, x);
        node->right(std::move(x));
        update_depth(node->right());
        update_depth(node);
    }

    // Recursive helper member function for search.
    std::optional<T> search_(T key, std::unique_ptr<Node<T>>& node)
    {
        if ( !node )                     return std::nullopt;
        if ( key == node->data ) return node->data;
        if ( key < node->data  ) return search_(key, node->left());
        else                     return search_(key, node->right());
    }

    // Recursive helper member function for finding maximum value
    T max_(std::unique_ptr<Node<T>>& node)
    {
        if ( !node->right() ) return node->data;
        else return max_(node->right());
    }

    // Recursive helper member function for finding minimum value
    T min_(std::unique_ptr<Node<T>>& node)
    {
        if ( !node->left() ) return node->data;
        else return min_(node->left());
    }

    // Recursive helper member function for extracting node with maximum value
    T extract_max_(std::unique_ptr<Node<T>>& it, std::unique_ptr<Node<T>>& its_parent)
    {
        if ( it->right() ) return extract_max_(it->right(), it);
        T result { it->data };
        if ( it == its_parent ) it = std::move(it->release_left());
        else
        {
            its_parent->right(it->release_left());
            balance_(its_parent);
        }
        return result;
    }
    static std::unique_ptr<Node<T>> extract_max_node_(std::unique_ptr<Node<T>>& it, std::unique_ptr<Node<T>>& its_parent)
    {
        if ( it->right() ) return extract_max_node_(it->right(), it);
        auto res { its_parent->release_right() };
        if ( it == its_parent ) it = std::move(it->release_left());
        else
        {
            its_parent->right(res->release_left());
            balance_(its_parent);
        }
        return std::move(res);
    }

    T extract_min_(std::unique_ptr<Node<T>>& it, std::unique_ptr<Node<T>>& its_parent)
    {
        T result;
        if ( it->left() )
        {
            result = extract_min_(it->left(), it);
            balance_(it);
            return result;
        }
        result = it->data;
        it = std::move(it->release_right());
        return result;
    }
    static std::unique_ptr<Node<T>> extract_min_node_(std::unique_ptr<Node<T>>& it, std::unique_ptr<Node<T>>& its_parent)
    {
        std::unique_ptr<Node<T>> result;
        if ( it->left() )
        {
            result = extract_min_node_(it->left(), it);
            balance_(it);
            return result;
        }
        result = its_parent->release_left();
        it = std::move(it->release_right());
        return std::move(result);
    }

    static void balance_(std::unique_ptr<Node<T>>& it)
    {
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
    // Recursive helper member function to delete node by its key
    bool remove_(T key, std::unique_ptr<Node<T>>& it, std::unique_ptr<Node<T>>& its_parent)
    {
        if ( !it ) return false;  // Key not found in the tree.
        if ( key == it->data )    // Base case: do the deletion.
        {
            switch ( parentage(it) )
            {
            case Parentage::none:       it.reset();                                        break;
            case Parentage::only_right: it = std::move(it->release_right());               break;
            case Parentage::only_left:  it = std::move(it->release_left());                break;
            case Parentage::both:       it->data = extract_min_(it->right(), it->right()); break;
            default: break;
            }
            return true;
        }
        else
        {
            bool res { false };
            if ( key < it->data ) res = remove_(key, it->left(), it);
            else if ( key > it->data ) res= remove_(key, it->right(), it);
            balance_(it);
            return res;
        }
    }


public:

    AVL() {}
    AVL(Node<T> root) : root_{root} {}
    AVL(T data)
    {
        root_ = std::make_unique<Node<T>>(data);
        root_->depth = 1;
    }

    std::unique_ptr<Node<T>>&  root() { return root_; };

    void add(T data)
    {
        if ( root_ == nullptr ) root_ = std::make_unique<Node<T>>(data);
        else                    add_(data, root_);
    }

    std::optional<T> search(T key)
    {
        return search_(key, root_);
    }

    bool remove(T key)
    {
        if ( root_ == nullptr ) return false;
        return remove_(key, root_, root_);
    }

    std::optional<T> max()
    {
        if ( root_ == nullptr ) return std::nullopt;
        return max_(root_);
    }

    std::optional<T> min()
    {
        if ( root_ == nullptr ) return std::nullopt;
        return min_(root_);
    }

    std::optional<T> extract_max()
    {
        if ( root_ == nullptr ) return std::nullopt;
        return extract_max_(root_, root_);
    }
    std::unique_ptr<Node<T>> extract_max_node()
    {
        if ( root_ == nullptr ) return nullptr;
        return extract_max_node_(root_, root_);
    }

    std::optional<T> extract_min()
    {
        if ( root_ == nullptr ) return std::nullopt;
        return extract_min_(root_, root_);
    }
    std::unique_ptr<Node<T>> extract_min_node()
    {
        if ( root_ == nullptr ) return nullptr;
        return extract_min_node_(root_, root_);
    }

    // Friends

    template<typename K> friend void print(const AVL<K>&);

    template<typename K, typename F> friend void in_order(const AVL<K>& tree, F fnc);
    template<typename K, typename F> friend void pre_order(const AVL<K>& tree, F fnc);
    template<typename K, typename F> friend void post_order(const AVL<K>& tree, F fnc);
    template<typename K, typename F> friend void level_order(const AVL<K>& tree, F fnc);

};

template<typename T>
void print(const AVL<T>& tree) { print(tree.root_); }

template<typename T, typename F>
void in_order(const AVL<T>& tree, F fnc) { in_order(tree.root_, fnc); }

template<typename T, typename F>
void pre_order(const AVL<T>& tree, F fnc) { pre_order(tree.root_, fnc); }

template<typename T, typename F>
void post_order(const AVL<T>& tree, F fnc) { post_order(tree.root_, fnc); }

template<typename T, typename F>
void level_order(const AVL<T>& tree, F fnc) { level_order(tree.root_, fnc); }

}  // namespace tree
