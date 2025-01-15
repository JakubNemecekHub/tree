#pragma once

#include <memory>

#include "linked.hpp"

namespace tree
{

enum class Child { left, right };

template<typename T>
class BST
{
private:

    std::unique_ptr<Node<T>> root_ { nullptr };

    // Recursive helper member function for adding nodes.
    void add_(T data, std::unique_ptr<Node<T>>& node)
    {
        if ( data <= node->data.value() )
        {
            if ( !node->left() ) node->left(data);
            else                 add_(data, node->left());

        }
        else
        {
            if ( !node->right() ) node->right(data);
            else                  add_(data, node->right());
        }
    }

    // Recursive helper member function for search.
    std::optional<T> search_(T key, std::unique_ptr<Node<T>>& node)
    {
        if ( !node )                     return std::nullopt;
        if ( key == node->data.value() ) return node->data;
        if ( key < node->data.value()  ) return search_(key, node->left());
        else                             return search_(key, node->right());
    }

    // Recursive helper member function for finding maximum value
    std::optional<T> max_(std::unique_ptr<Node<T>>& node)
    {
        if ( !node->right() ) return node->data;
        else return max_(node->right());
    }

    // Recursive helper member function for finding minimum value
    std::optional<T> min_(std::unique_ptr<Node<T>>& node)
    {
        if ( !node->left() ) return node->data;
        else return min_(node->left());
    }

    // Recursive helper member function for extracting node with maximum value value
    static std::optional<T> extract_max_(std::unique_ptr<Node<T>>& it, std::unique_ptr<Node<T>>& its_parent)
    {
        if ( it->right() ) return extract_max_(it->right(), it);
        T result { it->data.value() };
        if ( it == its_parent ) it.reset();
        else                    its_parent->right(it->release_left());
        return result;
    }
    static std::unique_ptr<Node<T>> extract_max_node_(std::unique_ptr<Node<T>>& it, std::unique_ptr<Node<T>>& its_parent)
    {
        if ( it->right() ) return extract_max_node_(it->right(), it);
        auto res { its_parent->release_right() };
        if ( it == its_parent ) it.reset();
        else                    its_parent->right(res->release_left());
        return std::move(res);
    }

    static std::optional<T> extract_min_(std::unique_ptr<Node<T>>& it, std::unique_ptr<Node<T>>& its_parent)
    {
        if ( it->left() ) return extract_min_(it->left(), it);
        T result { it->data.value() };
        if ( it == its_parent ) it.reset();
        else                    its_parent->left(it->release_right());
        return result;
    }
    static std::unique_ptr<Node<T>> extract_min_node_(std::unique_ptr<Node<T>>& it, std::unique_ptr<Node<T>>& its_parent)
    {
        if ( it->left() ) return extract_min_node_(it->left(), it);
        auto res { its_parent->release_left() };
        if ( it == its_parent ) it.reset();
        else                    its_parent->left(res->release_right());
        return std::move(res);
    }

    // Recursive helper member function to delete node by its key
    bool remove_(T key, std::unique_ptr<Node<T>>& it, std::unique_ptr<Node<T>>& its_parent, Child origin)
    {
        if ( key == it->data.value() )  // BASE CASE
        {
            if ( !it->left() && !it->right() )
            {
                if ( origin == Child::left ) its_parent->release_left();
                else                         its_parent->release_right();
                it.reset();
            }
            else if ( it->left() )
            {
                // Replace node's value by largest smaller value.
                it->data = extract_max_(it->left(), it->left()).value();
            }
            else
            {
                // Replace node's value by smallest larger value.
                it->data = extract_min_(it->right(), it->right()).value();
            }
            return true;
        }
        else if ( key < it->data.value() )
        {
            return remove_(key, it->left(), it, Child::left);
        }
        else
        {
            return remove_(key, it->right(), it, Child::right);
        }
        return false;
    }


public:

    BST() {}
    BST(Node<T> root) : root_{root} {}
    BST(T data)
    {
        root_ = std::make_unique<Node<T>>(data);
    }

    std::unique_ptr<Node<T>>&  root() { return root_; };

    void add(T data)
    {
        if ( root_ == nullptr ) root_ = std::make_unique<Node<T>>(data);
        else add_(data, root_);
    }

    std::optional<T> search(T key)
    {
        return search_(key, root_);
    }

    bool remove(T key)
    {
        if ( root_ == nullptr ) return false;
        return remove_(key, root_, root_, Child::left);
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

    template<typename K> friend void print(const BST<K>&);

    template<typename K, typename F> friend void in_order(const BST<K>& tree, F fnc);
    template<typename K, typename F> friend void pre_order(const BST<K>& tree, F fnc);
    template<typename K, typename F> friend void post_order(const BST<K>& tree, F fnc);
    template<typename K, typename F> friend void level_order(const BST<K>& tree, F fnc);

};

template<typename T>
void print(const BST<T>& tree) { print(tree.root_); }

template<typename T, typename F>
void in_order(const BST<T>& tree, F fnc) { in_order(tree.root_, fnc); }

template<typename T, typename F>
void pre_order(const BST<T>& tree, F fnc) { pre_order(tree.root_, fnc); }

template<typename T, typename F>
void post_order(const BST<T>& tree, F fnc) { post_order(tree.root_, fnc); }

template<typename T, typename F>
void level_order(const BST<T>& tree, F fnc) { level_order(tree.root_, fnc); }

}  // namespace tree
