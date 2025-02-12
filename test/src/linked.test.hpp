/*
    Test of Binary Tree
*/
#pragma once

#include "..\lib\suite.hpp"
#include "..\..\src\linked.hpp"


ts::Suite tests_BT { "Binary Tree" };

TEST(tests_BT, "Empty Binary tree must be full.")
{
    auto root { std::make_unique<tree::Node<int>>() };
    ASSERT
    (
        tree::is_full(root),
        "Empty Binary tree is not full."
    )
}

TEST(tests_BT, "Empty Binary tree must be complete.")
{
    auto root { std::make_unique<tree::Node<int>>() };
    ASSERT
    (
        tree::is_complete(root),
        "Empty Binary tree is not complete."
    )
}

TEST(tests_BT, "Empty Binary tree must be perfect.")
{
    auto root { std::make_unique<tree::Node<int>>() };
    ASSERT
    (
        tree::is_perfect(root),
        "Empty Binary tree is not perfect."
    )
}

TEST(tests_BT, "Empty Binary tree must be balanced.")
{
    auto root { std::make_unique<tree::Node<int>>() };
    ASSERT
    (
        tree::is_balanced(root),
        "Empty Binary tree is not balanced."
    )
}

// TO DO: Test character of non-empty trees.

TEST(tests_BT, "Parentage of node without children.")
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    ASSERT(
        tree::parentage(root) == tree::Parentage::none,
        "Parentage of node without children should be tree::Parentage::none."
    );
}
TEST(tests_BT, "Parentage of node with only left child.")
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    root->left(3);
    ASSERT(
        tree::parentage(root) == tree::Parentage::only_left,
        "Parentage of node with only left child should be tree::Parentage::only_left."
    );
}
TEST(tests_BT, "Parentage of node with only right child.")
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    root->right(3);
    ASSERT(
        tree::parentage(root) == tree::Parentage::only_right,
        "Parentage of node with only right child should be tree::Parentage::only_right."
    );
}
TEST(tests_BT, "Parentage of node with both children.")
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    root->right(3);
    root->left(3);
    ASSERT(
        tree::parentage(root) == tree::Parentage::both,
        "Parentage of node with both children should be tree::Parentage::both."
    );
}
