/*
    Test of Binary Tree
*/
#pragma once

#include "..\lib\suite.hpp"
#include "..\..\include\linked.hpp"


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

TEST(tests_BT, "Degree of node without children.")
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    ASSERT(
        tree::degree(root) == tree::Degree::none,
        "Degree of node without children should be tree::Degree::none."
    );
}
TEST(tests_BT, "Degree of node with only left child.")
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    root->left(3);
    ASSERT(
        tree::degree(root) == tree::Degree::only_left,
        "Degree of node with only left child should be tree::Degree::only_left."
    );
}
TEST(tests_BT, "Degree of node with only right child.")
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    root->right(3);
    ASSERT(
        tree::degree(root) == tree::Degree::only_right,
        "Degree of node with only right child should be tree::Degree::only_right."
    );
}
TEST(tests_BT, "Degree of node with both children.")
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    root->right(3);
    root->left(3);
    ASSERT(
        tree::degree(root) == tree::Degree::both,
        "Degree of node with both children should be tree::Degree::both."
    );
}
