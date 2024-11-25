#pragma once

#include <optional>
#include <queue>
#include <functional>

namespace tree
{

template<typename T>
class Node
{
private:

    Node* right_ { nullptr };
    Node* left_  { nullptr };

public:

    std::optional<T> data { std::nullopt };

    Node() {}
    Node(T data_) : data {data_} {}
    Node(T data_, Node* right, Node* left)
        : data {data_}, right_{right}, left_{left} {}

    void right(Node* child) { right_ = child; }
    Node* right(T data)
    {
        right_ = new Node<T>(data);
        return right_;
    }
    Node* right() const { return right_; }
    void left(Node* child) { left_ = child; }
    Node* left(T data)
    {
        left_ = new Node<T>(data);
        return left_;
    }
    Node* left() const { return left_; }

    // Serialization
    template<typename K> friend void serialize(const Node<K>*, std::ostream&);

    // Height
    // Depth of a node -> HOW? Is it usefull on its own?
    // Path between two nodes?

    template<typename K> friend size_t height(const Node<K>*);
    template<typename K> friend size_t count_nodes(const Node<K>*);

    // Traversals

    template<typename K> friend void print_tree(const Node<K>*, int);

    template<typename K, typename F> friend void in_order(const Node<K>*, F);
    template<typename K, typename F> friend void pre_order(const Node<K>*, F);
    template<typename K, typename F> friend void post_order(const Node<K>*, F);
    template<typename K, typename F> friend void level_order(const Node<K>*, F);

    // Tree Type

    template<typename K> friend bool is_full(const Node<K>*);
    template<typename K> friend bool is_complete(const Node<K>*, size_t);
    template<typename K> friend bool is_perfect(const Node<K>*, size_t);
    template<typename K> friend bool is_balanced(const Node<K>*);

};

// Serialization

template<typename T>
void serialize(const Node<T>* root, std::ostream& out)
{
    if ( root == nullptr ) {
        out << "# ";  // Use "#" to denote a null node
        return;
    }
    out << root->data.value() << " "; // Serialize current node's data
    serialize(root->left_, out);      // Serialize left subtree
    serialize(root->right_, out);     // Serialize right subtree
}

template<typename T>
Node<T>* deserialize(std::ifstream& in)
{
    std::string val;
    in >> val;

    if (val == "#") {
        return nullptr;  // If the value is "#", it represents a null node
    }

    T data = std::stoi(val);
    Node<T>* node = new Node<T>(data);
    node->left(deserialize<T>(in));  // Rebuild left subtree
    node->right(deserialize<T>(in)); // Rebuild right subtree
    return node;
}

// Height of the tree

template<typename T>
size_t height(const Node<T>* root)
{
    if ( root == nullptr ) return 0;
    size_t height_left  { height(root->left_)  };
    size_t height_right { height(root->right_) };
    return std::max(height_left, height_right) + 1;
}

template<typename T>
size_t count_nodes(const Node<T>* node)
{
    if ( node == nullptr ) return 0;
    return (count_nodes(node->left_) + count_nodes(node->right_) + 1);
}

// Recursive function to display the tree sideways
template<typename T>
void print_tree(const Node<T>* node, int depth = 0)
{
    if (node == nullptr) return;
    print_tree(node->right_, depth + 1);
    std::cout << std::string(4 * depth, ' ') << node->data.value() << std::endl;
    print_tree(node->left_, depth + 1);
}




// Traversals

template<typename T, typename F>
void in_order(const Node<T>* root, F fnc)
{
    if ( root == nullptr ) return;
    in_order(root->left_, fnc);
    fnc(root->data);
    in_order(root->right_, fnc);
}

template<typename T, typename F>
void pre_order(const Node<T>* root, F fnc)
{
    if ( root == nullptr ) return;
    fnc(root->data);
    pre_order(root->left_, fnc);
    pre_order(root->right_, fnc);
}

template<typename T, typename F>
void post_order(const Node<T>* root, F fnc)
{
    if ( root == nullptr ) return;
    post_order(root->left_, fnc);
    post_order(root->right_, fnc);
    fnc(root->data);
}

template<typename T, typename F>
void level_order(const Node<T>* root, F fnc)
{
    std::queue<const Node<T>*> q;
    q.push(root);
    while ( !q.empty() )
    {
        const Node<T>* it { q.front() };
        q.pop();
        fnc(it->data);
        if ( it->left_ != nullptr )  q.push(it->left_);
        if ( it->right_ != nullptr ) q.push(it->right_);
    }
}

// Tree Type

/*
    Every node in a full binary tree has either 0 or 2 children.

    Alson known as a proper binary tree.
*/
template<typename T>
bool is_full(const Node<T>* node)
{
  if ( node == nullptr ) return true;
  if ( node->left_ == nullptr && node->right_ == nullptr ) return true;   // Base case

  if ( node->left_ && node->right_ )
    return (is_full(node->left_) && is_full(node->right_));
  return false;
}

/*
    In a complete binary tree every level, except possibly the last, is completely
    filled and all nodes at the last level are as far as possible.
*/
template<typename T>
bool is_complete(const Node<T>* node, size_t index = 0)
{
    static size_t node_count { count_nodes(node) };
    if ( node == nullptr ) return true;
    if ( index >= node_count ) return false;
    return (is_complete(node->left_, 2 * index + 1) && is_complete(node->right_, 2 * index + 2));
}

/*
    All parents in a perfect binary tree have exactly 2 chidlren, and
    all leaves are on the same level.

    Every perfect binary tree is full and perfect.
*/
template<typename T>
bool is_perfect(const Node<T>* node, size_t level = 0)
{
    static size_t tree_height { height(node) };
    if ( node == nullptr ) return true;
    if ( node->left_ == nullptr && node->right_ == nullptr)
        return (tree_height == level + 1);  // We got a leaf. Check if it is at the last level.
    if ( node->left_ == nullptr || node->right_ == nullptr )
        return false;                       // Internal node with only one child.
                                            // Such nodes cannot exist in a perfect tree.
    // If we have a internal node with both children, we must check both its subtrees.
    return is_perfect(node->left_, level + 1) &&
           is_perfect(node->right_, level + 1);
}

/*
    The height of both subtrees of every node differs by at most 1.
*/
template<typename T>
bool is_balanced(const Node<T>* node)
{
    std::queue<const Node<T>*> q;
    q.push(node);
    while ( !q.empty() )
    {
        const Node<T>* it { q.front() };
        q.pop();

        size_t height_left  { height(it->left_)  };
        size_t height_right { height(it->right_) };
        if ( (height_left >= (height_right + 2)) || (height_right >= (height_left + 2)) ) return false;

        if ( it->left_ != nullptr )  q.push(it->left_);
        if ( it->right_ != nullptr ) q.push(it->right_);
    }
    return true;
}

}  // namespace tree
