#pragma once

#include <stack>

#include "linked.hpp"


namespace tree
{

template<typename T>
class InOrderIterator
{
private:

    /*
        Forward iterator

        Operators that seem to be necessary:
        pre-increment operator operator++() -> moves iterator to next value.
        dereference operator operator*()    -> Gets value
        and equality operators operator==() -> What are these supposed to do?
                           and operator!=()
    */

    std::stack<Node<T>*> stack_;

    void push_left_(Node<T>* node)
    {
        while(node)
        {
            stack_.push(node);
            node = node->left().get();
        }
    }

public:

    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    InOrderIterator(Node<T>* root)
    {
        push_left_(root);
    }

    value_type operator*() const
    {
        return stack_.top()->data;
    }

    InOrderIterator<T>& operator++()    // Pre-increment
    {
        auto node { stack_.top() };
        stack_.pop();
        push_left_(node->right().get());
        return *this;
    }
    InOrderIterator<T> operator++(int)  // Post-increment
    {
        InOrderIterator temp { *this };
        ++(*this);
        return temp;
    }

    bool operator!=(const InOrderIterator& other) const
    {
        return !(*this == other);
    }

    bool operator==(const InOrderIterator& other) const
    {
        return stack_.empty() && other.stack_.empty();  // TO DO: Check the logic behind this.

    }

};

} // namespace tree
