/*
    Test of Binary Search Tree
*/
#pragma once

#include <algorithm>

#include "..\lib\ts\suite.hpp"
#include "..\..\include\bst.hpp"


ts::Suite tests_BST { "Binary Search Tree" };

TEST(tests_BST, "Number of nodes in empty tree must be 0.")
{
    tree::BST<int> search_tree;
    ASSERT_EQ( tree::count_nodes(search_tree.root()), 0 )
}

TEST(tests_BST, "Height of empty tree must be 0.")
{
    tree::BST<int> search_tree;
    ASSERT_EQ( tree::height(search_tree.root()), 0 )
}

TEST(tests_BST, "Empty BST must be full.")
{
    tree::BST<int> search_tree;
    ASSERT_TRUE( tree::is_full(search_tree.root()) )
}

TEST(tests_BST, "Empty BST must be complete.")
{
    tree::BST<int> search_tree;
    ASSERT_TRUE( tree::is_complete(search_tree.root()) )
}

TEST(tests_BST, "Empty BST must be perfect.")
{
    tree::BST<int> search_tree;
    ASSERT_TRUE( tree::is_perfect(search_tree.root()) )
}

TEST(tests_BST, "Empty BST must be balanced.")
{
    tree::BST<int> search_tree;
    ASSERT_TRUE( tree::is_balanced(search_tree.root()) )
}

TEST(tests_BST, "Adding to empty tree.")
{
    tree::BST<int> search_tree;
    search_tree.add(7);
    ASSERT_TRUE( search_tree.root() )
}

tree::BST<int> set_up_bst()
{
    tree::BST<int> search_tree;
    search_tree.add(7);
    search_tree.add(2);
    search_tree.add(56);
    search_tree.add(8);
    search_tree.add(23);
    search_tree.add(3);
    return search_tree;
}

void bst_property_(tree::BST<int>& search_tree)
{
    int value { INT_MIN };
    for ( auto it {search_tree.begin()}; it != search_tree.end(); ++it)
    {
        ASSERT_TRUE( *it >= value )
        value = *it;
    }
}

TEST(tests_BST, "BST fullfills the BST property.")
{
    auto search_tree { set_up_bst() };
    bst_property_(search_tree);
}

TEST(tests_BST, "Result of a search for existing key has a valid value.")
{
    auto search_tree { set_up_bst() };
    ASSERT_TRUE( search_tree.search(56).has_value() )
}
TEST(tests_BST, "Result of a search for existing key has a correct value.")
{
    auto search_tree { set_up_bst() };
    ASSERT_EQ( search_tree.search(56).value(), 56 )
}

TEST(tests_BST, "Result of a search for non-existing key is std::nullopt.")
{
    auto search_tree { set_up_bst() };
    ASSERT_EQ_M( search_tree.search(222), std::nullopt )
}

TEST(tests_BST, "Adding key preserves the BST property.")
{
    auto search_tree { set_up_bst() };
    search_tree.add(666);
    bst_property_(search_tree);
}

TEST(tests_BST, "Removing key preserves the BST property.")
{
    auto search_tree { set_up_bst() };
    search_tree.remove(23);
    bst_property_(search_tree);

}

TEST(tests_BST, "Removing existing key returns true.")
{
    auto search_tree { set_up_bst() };
    ASSERT_TRUE( search_tree.remove(23) )
}
TEST(tests_BST, "Removed key is no longer in BST.")
{
    auto search_tree { set_up_bst() };
    search_tree.remove(23);
    ASSERT_EQ_M( search_tree.search(23), std::nullopt )
}

TEST(tests_BST, "Removing non-existing key returns false.")
{
    auto search_tree { set_up_bst() };
    ASSERT_FALSE( search_tree.remove(222) )
}

/*
    min and max
*/
TEST(tests_BST, "max returns the maximum value.")
{
    auto search_tree { set_up_bst() };
    auto maximum { search_tree.max() };
    std::for_each(search_tree.begin(), search_tree.end(), [maximum](int value)
    {
        ASSERT_TRUE( value <= maximum )
    });
}
TEST(tests_BST, "Maximum of empty BST is std::nullopt.")
{
    tree::BST<int> search_tree;
    ASSERT_EQ_M( search_tree.max(), std::nullopt )
}


TEST(tests_BST, "min returns the minimum value.")
{
    auto search_tree { set_up_bst() };
    auto minimum { search_tree.min() };
    std::for_each(search_tree.begin(), search_tree.end(), [minimum](int value)
    {
        ASSERT_TRUE( value >= minimum )
    });
}
TEST(tests_BST, "Minimum of empty BST is std::nullopt.")
{
    tree::BST<int> search_tree;
    ASSERT_EQ_M( search_tree.max(), std::nullopt )
}

/*
    extract min and extract max
*/
TEST(tests_BST, "Extracted maximum is larger that remaining keys.")
{
    auto search_tree { set_up_bst() };
    auto maximum { search_tree.extract_max() };
    std::for_each(search_tree.begin(), search_tree.end(), [maximum](int value)
    {
        ASSERT_TRUE( value <= maximum )
    });
}
TEST(tests_BST, "Extracted maximum is removed from tree.")
{
    auto search_tree { set_up_bst() };
    auto maximum { search_tree.extract_max() };
    ASSERT_EQ_M( search_tree.search(maximum.value()), std::nullopt )
}
TEST(tests_BST, "Extracted maximum from empty tree is std::nullopt.")
{
    tree::BST<int> search_tree;
    ASSERT_EQ_M( search_tree.extract_max(), std::nullopt )
}

TEST(tests_BST, "Extracted minimum is smaller that remaining keys.")
{
    auto search_tree { set_up_bst() };
    auto minimum { search_tree.extract_min() };
    std::for_each(search_tree.begin(), search_tree.end(), [minimum](int value)
    {
        ASSERT_TRUE( value >= minimum )
    });
}
TEST(tests_BST, "Extracted minimum is removed from tree.")
{
    auto search_tree { set_up_bst() };
    auto minimum { search_tree.extract_min() };
    ASSERT_EQ_M( search_tree.search(minimum.value()), std::nullopt )
}
TEST(tests_BST, "Extracted minimum from empty tree is std::nullopt.")
{
    tree::BST<int> search_tree;
    ASSERT_EQ_M( search_tree.extract_min(), std::nullopt )
}

/*
    extract min node and extract max node
*/
TEST(tests_BST, "Extracted maximum node is larger that remaining keys.")
{
    auto search_tree { set_up_bst() };
    auto maximum { search_tree.extract_max_node() };
    std::for_each(search_tree.begin(), search_tree.end(), [&maximum](int value)
    {
        ASSERT_TRUE( value <= maximum->data )
    });
}
TEST(tests_BST, "Extracted maximum node is removed from tree.")
{
    auto search_tree { set_up_bst() };
    auto maximum { search_tree.extract_max_node() };
    ASSERT_EQ_M( search_tree.search(maximum->data), std::nullopt )
}
TEST(tests_BST, "Extracted maximum node from empty tree is nullptr.")
{
    tree::BST<int> search_tree;
    ASSERT_FALSE( search_tree.extract_max_node() )
}

TEST(tests_BST, "Extracted minimum node is smaller that remaining keys.")
{
    auto search_tree { set_up_bst() };
    auto minimum { search_tree.extract_min_node() };
    std::for_each(search_tree.begin(), search_tree.end(), [&minimum](int value)
    {
        ASSERT_TRUE( value >= minimum->data )
    });
}
TEST(tests_BST, "Extracted minimum node is removed from tree.")
{
    auto search_tree { set_up_bst() };
    auto minimum { search_tree.extract_min_node() };
    ASSERT_EQ_M( search_tree.search(minimum->data), std::nullopt )
}
TEST(tests_BST, "Extracted minimum node from empty tree is nullptr.")
{
    tree::BST<int> search_tree;
    ASSERT_FALSE( search_tree.extract_min_node() )
}
