/*
    Test of Binary Search Tree
*/
#pragma once

#include <algorithm>

#include "..\lib\suite.hpp"
#include "..\..\include\bst.hpp"


ts::Suite tests_BST { "Binary Search Tree" };

TEST(tests_BST, "Empty tree creation.")
{
    tree::BST<int> search_tree;
    ASSERT
    (
        !search_tree.root(),
        "Root of empty BST is not nullptr."
    )
}

TEST(tests_BST, "Number of nodes in empty tree must be 0.")
{
    tree::BST<int> search_tree;
    ASSERT
    (
        tree::count_nodes(search_tree.root()) == 0,
        "Number of nodes in empty tree is not 0."
    )
}

TEST(tests_BST, "Height of empty tree must be 0.")
{
    tree::BST<int> search_tree;
    ASSERT
    (
        tree::height(search_tree.root()) == 0,
        "Height of empty tree is not 0."
    )
}

TEST(tests_BST, "Non-empty tree creation.")
{
    tree::BST<int> search_tree { 7 };
    ASSERT
    (
        search_tree.root(),
        "Root of non-empty BST is nullptr."
    )
}

TEST(tests_BST, "Adding to empty tree.")
{
    tree::BST<int> search_tree;
    search_tree.add(7);
    ASSERT
    (
        search_tree.root(),
        "Root of previously empty BST is nullptr after adding a value."

    )
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
        ASSERT
        (
            *it >= value,
            "Key in BST not in order."
        )
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
    ASSERT
    (
        search_tree.search(56).has_value(),
        "Search for existing key doesn't have value."
    )
}
TEST(tests_BST, "Result of a search for existing key has a correct value.")
{
    auto search_tree { set_up_bst() };
    ASSERT
    (
        search_tree.search(56).value() == 56,
        "Search returns wrong value."
    )
}

TEST(tests_BST, "Result of a search for non-existing key is std::nullopt.")
{
    auto search_tree { set_up_bst() };
    ASSERT
    (
        search_tree.search(222) == std::nullopt,
        "Search for non existing value doesn't return std::nullopt."
    )
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
    ASSERT
    (
        search_tree.remove(23),
        "Removing existing key returned false."
    )

}
TEST(tests_BST, "Removed key is no longer in BST.")
{
    auto search_tree { set_up_bst() };
    search_tree.remove(23);
    ASSERT
    (
        search_tree.search(23) == std::nullopt,
        "Removing existing key didn't remove it."
    )
}

TEST(tests_BST, "Removing non-existing key returns false.")
{
    auto search_tree { set_up_bst() };
    ASSERT
    (
        !search_tree.remove(222),
        "Removing non-existing key returned true."
    )
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
        ASSERT
        (
            value <= maximum,
            "max does not return the maximum value."
        )
    });
}
TEST(tests_BST, "Maximum of empty BST is std::nullopt.")
{
    tree::BST<int> search_tree;
    ASSERT
    (
        search_tree.max() == std::nullopt,
        "Maximum of empty BTS is not std::nullopt."
    )
}


TEST(tests_BST, "min returns the minimum value.")
{
    auto search_tree { set_up_bst() };
    auto minimum { search_tree.min() };
    std::for_each(search_tree.begin(), search_tree.end(), [minimum](int value)
    {
        ASSERT
        (
            value >= minimum,
            "min does not return the minimum value."
        )
    });
}
TEST(tests_BST, "Minimum of empty BST is std::nullopt.")
{
    tree::BST<int> search_tree;
    ASSERT
    (
        search_tree.max() == std::nullopt,
        "Minimum of empty BTS is not std::nullopt."
    )
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
        ASSERT
        (
            value <= maximum,
            "extract_max doesn't extract the maximum value."
        )
    });
}
TEST(tests_BST, "Extracted maximum is removed from tree.")
{
    auto search_tree { set_up_bst() };
    auto maximum { search_tree.extract_max() };
    ASSERT
    (
        search_tree.search(maximum.value()) == std::nullopt,
        "extract_max doesn't remove extracted key from tree."
    )
}
TEST(tests_BST, "Extracted maximum from empty tree is std::nullopt.")
{
    tree::BST<int> search_tree;
    ASSERT
    (
        search_tree.extract_max() == std::nullopt,
        "extract_max extracts something from an empty tree."
    )
}

TEST(tests_BST, "Extracted minimum is smaller that remaining keys.")
{
    auto search_tree { set_up_bst() };
    auto minimum { search_tree.extract_min() };
    std::for_each(search_tree.begin(), search_tree.end(), [minimum](int value)
    {
        ASSERT
        (
            value >= minimum,
            "extract_min doesn't extract the minimum value."
        )
    });
}
TEST(tests_BST, "Extracted minimum is removed from tree.")
{
    auto search_tree { set_up_bst() };
    auto minimum { search_tree.extract_min() };
    ASSERT
    (
        search_tree.search(minimum.value()) == std::nullopt,
        "extract_min doesn't remove extracted key from tree."
    )
}
TEST(tests_BST, "Extracted minimum from empty tree is std::nullopt.")
{
    tree::BST<int> search_tree;
    ASSERT
    (
        search_tree.extract_min() == std::nullopt,
        "extract_min extracts something from an empty tree."
    )
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
        ASSERT
        (
            value <= maximum->data,
            "extract_max_node doesn't extract the maximum value."
        )
    });
}
TEST(tests_BST, "Extracted maximum node is removed from tree.")
{
    auto search_tree { set_up_bst() };
    auto maximum { search_tree.extract_max_node() };
    ASSERT
    (
        search_tree.search(maximum->data) == std::nullopt,
        "extract_max_node doesn't remove extracted key from tree."
    )
}
TEST(tests_BST, "Extracted maximum node from empty tree is nullptr.")
{
    tree::BST<int> search_tree;
    ASSERT
    (
        !search_tree.extract_max_node(),
        "extract_max_node extracts something from an empty tree."
    )
}

TEST(tests_BST, "Extracted minimum node is smaller that remaining keys.")
{
    auto search_tree { set_up_bst() };
    auto minimum { search_tree.extract_min_node() };
    std::for_each(search_tree.begin(), search_tree.end(), [&minimum](int value)
    {
        ASSERT
        (
            value >= minimum->data,
            "extract_min_node doesn't extract the minimum value."
        )
    });
}
TEST(tests_BST, "Extracted minimum node is removed from tree.")
{
    auto search_tree { set_up_bst() };
    auto minimum { search_tree.extract_min_node() };
    ASSERT
    (
        search_tree.search(minimum->data) == std::nullopt,
        "extract_min_node doesn't remove extracted key from tree."
    )
}
TEST(tests_BST, "Extracted minimum node from empty tree is nullptr.")
{
    tree::BST<int> search_tree;
    ASSERT
    (
        !search_tree.extract_min_node(),
        "extract_min_node extracts something from an empty tree."
    )
}
