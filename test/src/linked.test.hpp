/*
    Test of Binary Tree
*/
#pragma once

#include "..\lib\ts\suite.hpp"
#include "..\..\include\linked.hpp"


ts::Suite tests_BT { "Binary Tree" };

TEST(tests_BT, "Degree of node without children.")
{
    tree::Node<int> root { 7 };
    ASSERT_EQ_M( root.degree(), tree::Degree::none )
}
TEST(tests_BT, "Degree of node with only left child.")
{
    tree::Node<int> root { 7 };
    root.left(3);
    ASSERT_EQ_M( root.degree(), tree::Degree::only_left )
}
TEST(tests_BT, "Degree of node with only right child.")
{
    tree::Node<int> root { 7 };
    root.right(3);
    ASSERT_EQ_M( root.degree(), tree::Degree::only_right )
}
TEST(tests_BT, "Degree of node with both children.")
{
    tree::Node<int> root { 7 };
    root.right(3);
    root.left(3);
    ASSERT_EQ_M( root.degree(), tree::Degree::both )
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

/*
    Children
*/
TEST(tests_BT, "Add children.")
{
    tree::Node<int> root { 7 };
    tree::Node<int> left { 6 };
    tree::Node<int> right { 8 };
    root.left(std::move(left));
    root.right(std::move(right));
}
