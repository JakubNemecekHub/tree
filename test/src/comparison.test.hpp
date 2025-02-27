/*
    Test of comparison of two trees.

    Operator == compares only data in the root. tree::compare, on the other hand,
    compares the whole trees (e.g. data and structure of all nodes).
*/
#pragma once

#include "..\lib\ts\suite.hpp"
#include "..\..\include\linked.hpp"
#include "..\..\include\avl.hpp"


ts::Suite tests_comparison { "Comparison of two trees." };

/*
    Identical trees
*/
TEST(tests_comparison, "Only roots, and they have different data.")
{
    auto root_1 { std::make_unique<tree::Node<int>>(7) };
    auto root_2 { std::make_unique<tree::Node<int>>(8) };
    ASSERT_FALSE( tree::compare(root_1, root_2) )
}

TEST(tests_comparison, "Small tree with same structure but different data (1).")
{
    auto root_1 { std::make_unique<tree::Node<int>>(7) };
    root_1->left(5);
    auto root_2 { std::make_unique<tree::Node<int>>(7) };
    root_2->left(4);
    ASSERT_FALSE( tree::compare(root_1, root_2) )
}

TEST(tests_comparison, "Small tree with same structure but different data (2).")
{
    auto root_1 { std::make_unique<tree::Node<int>>(7) };
    root_1->right(5);
    auto root_2 { std::make_unique<tree::Node<int>>(7) };
    root_2->right(4);
    ASSERT_FALSE( tree::compare(root_1, root_2) )
}

TEST(tests_comparison, "Small tree with different structure.")
{
    auto root_1 { std::make_unique<tree::Node<int>>(7) };
    root_1->right(5);
    auto root_2 { std::make_unique<tree::Node<int>>(7) };
    ASSERT_FALSE( tree::compare(root_1, root_2) )
}

/*
    Different trees
*/
TEST(tests_comparison, "Tree with only identical roots.")
{
    auto root_1 { std::make_unique<tree::Node<int>>(7) };
    auto root_2 { std::make_unique<tree::Node<int>>(7) };
    ASSERT_TRUE( tree::compare(root_1, root_2) )
}

TEST(tests_comparison, "Small tree with same structure and data (1).")
{
    auto root_1 { std::make_unique<tree::Node<int>>(7) };
    root_1->left(5);
    auto root_2 { std::make_unique<tree::Node<int>>(7) };
    root_2->left(5);
    ASSERT_TRUE( tree::compare(root_1, root_2) )
}

TEST(tests_comparison, "Small tree with same structure and data (2).")
{
    auto root_1 { std::make_unique<tree::Node<int>>(7) };
    root_1->right(5);
    auto root_2 { std::make_unique<tree::Node<int>>(7) };
    root_2->right(5);
    ASSERT_TRUE( tree::compare(root_1, root_2) )
}

/*
    AVL
*/
TEST(tests_comparison, "Identical AVL trees.")
{
    tree::AVL<int> tree_1;
    tree_1.add(1);
    tree_1.add(2);
    tree_1.add(3);
    tree_1.add(4);
    tree_1.add(5);
    tree::AVL<int> tree_2;
    tree_2.add(1);
    tree_2.add(2);
    tree_2.add(3);
    tree_2.add(4);
    tree_2.add(5);
    ASSERT_TRUE( tree::compare(tree_1.root(), tree_2.root()) )
}

TEST(tests_comparison, "Different AVL trees.")
{
    tree::AVL<int> tree_1;
    tree_1.add(1);
    tree_1.add(2);
    tree_1.add(3);
    tree_1.add(4);
    tree_1.add(5);
    tree::AVL<int> tree_2;
    tree_2.add(1);
    tree_2.add(2);
    tree_2.add(66);
    tree_2.add(4);
    tree_2.add(5);
    ASSERT_FALSE( tree::compare(tree_1.root(), tree_2.root()) )
}

