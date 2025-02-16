/*
    Test of Binary Tree
*/
#pragma once

#include "..\lib\ts\suite.hpp"
#include "..\..\include\linked.hpp"


ts::Suite tests_BT { "Binary Tree" };

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

/*
    Full Binary tree
        1
       / \
      2   3
     / \
    4   5
*/
TEST(tests_BT, "Full Binary tree.")
{
    auto root { std::make_unique<tree::Node<int>>(1) };
    root->right(3);
    auto& left_child { root->left(2) };
    left_child->left(4);
    left_child->right(5);
    ASSERT_TRUE ( tree::is_full(root) )
}

/*
    Complete Binary tree
         1
       /   \
      2     3
     / \   /
    4   5 6
*/
TEST(tests_BT, "Complete Binary tree.")
{
    auto root { std::make_unique<tree::Node<int>>(1) };
    auto& right_child { root->right(3) };
    right_child->left(6);
    auto& left_child { root->left(2) };
    left_child->left(4);
    left_child->right(5);
    ASSERT_TRUE ( tree::is_complete(root) )
    ASSERT_TRUE ( tree::is_balanced(root) )
}

/*
    Perfect Binary Tree
*/
TEST(tests_BT, "Perfect Binary Tree.")
{
    auto root { std::make_unique<tree::Node<int>>(1) };
    auto& right_child { root->right(3) };
    right_child->left(6);
    right_child->right(7);
    auto& left_child { root->left(2) };
    left_child->left(4);
    left_child->right(5);
    ASSERT_TRUE ( tree::is_perfect(root)  )  // NOT
    ASSERT_TRUE ( tree::is_complete(root) )  // NOT OK
    ASSERT_TRUE ( tree::is_full(root)     )  // OK
    ASSERT_TRUE ( tree::is_balanced(root) )  // OK
}

/*
    Balanced Binary tree
*/
TEST(tests_BT, "Balanced Binary tree.")
{
    auto root { std::make_unique<tree::Node<int>>(1) };
    auto& right_child { root->right(3) };
    right_child->left(6);
    right_child->right(7);
    auto& left_child { root->left(2) };
    left_child->left(4);
    left_child->right(5);
    ASSERT_TRUE ( tree::is_balanced(root) )
}
