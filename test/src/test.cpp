#include "..\lib\harness.hpp"
#include "..\..\src\avl.hpp"
#include "linked.test.hpp"
#include "avl.test.hpp"

#include <iostream>

int main()
{
    TestSuite suite;

    /*
        Nodes
    */
   suite.add("Correct Parentage of a Node without children.", parentage_none);
   suite.add("Correct Parentage of a Node both children.", parentage_both);
   suite.add("Correct Parentage of a Node with only right children.", parentage_only_right);
   suite.add("Correct Parentage of a Node with only left children.", parentage_only_left);

    /*
        AVL
    */

    suite.add("Height of empty tree must be 0.", [](){
        tree::AVL<int> tree;
        auto height { tree::height(tree.root()) };
        if ( height != 0 ) throw std::runtime_error("Height of empty tree is not 0.");
    });

    suite.add("Number of nodes in empty tree must be 0.", [](){
        tree::AVL<int> tree;
        auto node_count { tree::count_nodes(tree.root()) };
        if ( node_count != 0 ) throw std::runtime_error("Number of nodes in empty tree is not 0.");
    });

    suite.add("Empty AVL must be full.", [](){
        tree::AVL<int> tree;
        auto is_full { tree::is_full(tree.root()) };
        if ( !is_full ) throw std::runtime_error("Empty AVL is not full.");
    });

    suite.add("Empty AVL must be complete.", [](){
        tree::AVL<int> tree;
        auto is_complete { tree::is_complete(tree.root()) };
        if ( !is_complete ) throw std::runtime_error("Empty AVL is not complete.");
    });

    suite.add("Empty AVL must be perfect.", [](){
        tree::AVL<int> tree;
        auto is_perfect { tree::is_perfect(tree.root()) };
        if ( !is_perfect ) throw std::runtime_error("Empty AVL is not perfect.");
    });

    suite.add("Empty AVL must be balanced.", [](){
        tree::AVL<int> tree;
        auto is_balanced { tree::is_balanced(tree.root()) };
        if ( !is_balanced ) throw std::runtime_error("Empty AVL is not balanced.");
    });

    suite.add("Searching empty AVL must return nullopt.", [](){
        tree::AVL<int> tree;
        auto search_result { tree.search(45) };
        if ( search_result != std::nullopt ) throw std::runtime_error("Search in empty tree doesn't return nullopt.");

    });

    suite.add("Removing from empty AVL must return false.", [](){
        tree::AVL<int> tree;
        auto remove_result { tree.remove(45) };
        if ( remove_result != false ) throw std::runtime_error("Removing anything from empty tree doesn't return false.");

    });

    suite.add("max member function of empty AVL must return nullopt.", [](){
        tree::AVL<int> tree;
        auto max_result { tree.max() };
        if ( max_result != std::nullopt ) throw std::runtime_error("max member function of empty AVL doesn't return nullptr.");
    });

    suite.add("min member function of empty AVL must return nullopt.", [](){
        tree::AVL<int> tree;
        auto min_result { tree.min() };
        if ( min_result != std::nullopt ) throw std::runtime_error("min member function of empty AVL doesn't return nullptr.");
    });

    suite.add("extract_max member function of empty AVL must return nullopt.", [](){
        tree::AVL<int> tree;
        auto extract_max_result { tree.extract_max() };
        if ( extract_max_result != std::nullopt ) throw std::runtime_error("extract_max member function of empty AVL doesn't return nullopt.");
    });

    suite.add("extract_min member function of empty AVL must return nullopt.", [](){
        tree::AVL<int> tree;
        auto extract_min_result { tree.extract_min() };
        if ( extract_min_result != std::nullopt ) throw std::runtime_error("extract_min member function of empty AVL doesn't return nullopt.");
    });

    suite.add("extract_max_node member function of empty AVL must return nullptr.", [](){
        tree::AVL<int> tree;
        auto extract_max_node_result { tree.extract_max_node() };
        if ( extract_max_node_result != nullptr ) throw std::runtime_error("extract_max_node member function of empty AVL doesn't return nullptr.");
    });

    suite.add("extract_min_node member function of empty AVL must return nullptr.", [](){
        tree::AVL<int> tree;
        auto extract_min_node_result { tree.extract_min_node() };
        if ( extract_min_node_result != nullptr ) throw std::runtime_error("extract_min_node member function of empty AVL doesn't return nullptr.");
    });

    suite.add("Tree stays balanced during insertion.", test_add);
    suite.add("Tree stays balanced during deletion.", test_remove);

    suite.run();
    return 0;
}
