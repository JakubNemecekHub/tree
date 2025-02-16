/*
    Test various construction of BST and AVL
*/
#pragma once

#include <optional>
#include <string>

#include "..\lib\ts\suite.hpp"
#include "..\..\include\avl.hpp"

/*
    Some comparable data
*/
struct C_Data
{
    int number; std::string text;
    auto operator<=>(const C_Data& other) const
    {
        return number <=> other.number;
    }
    bool operator==(const C_Data& other) const
    {
        return number == other.number;
    }
};
struct C_NData
{
    int number; std::string text;
    C_NData(int _number, std::string _text)
        : number{_number}, text{_text} {}
    auto operator<=>(const C_NData& other) const
    {
        return number <=> other.number;
    }
    bool operator==(const C_NData& other) const
    {
        return number == other.number;
    }
};
struct C_DData
{
    int number; std::string text;
    C_DData() : number{0}, text{"Name"} {}
    auto operator<=>(const C_DData& other) const
    {
        return number <=> other.number;
    }
    bool operator==(const C_DData& other) const
    {
        return number == other.number;
    }
};

/*
    Test various construction of BST and AVL
*/
ts::Suite tests_bst_constructor { "Testing various construction of BST." };

TEST(tests_bst_constructor, "Empty BST creation.")
{
    tree::BST<int> tree_0;
    tree::BST<int> tree_1 {};
    ASSERT_FALSE( tree_0.root() )
    ASSERT_FALSE( tree_1.root() )
    tree::BST<C_Data> tree_2 {};
    tree::BST<C_NData> tree_3 {};
    tree::BST<C_DData> tree_4 {};
    ASSERT_FALSE( tree_2.root() )
    ASSERT_FALSE( tree_3.root() )
    ASSERT_FALSE( tree_4.root() )
}

TEST(tests_bst_constructor, "BST<int> directly.")
{
    tree::BST<int> bs_tree { 7 };
    ASSERT_TRUE( bs_tree.root() )
    ASSERT_TRUE( bs_tree.search(7).has_value() )
    ASSERT_EQ( bs_tree.search(7).value(), 7)

}
TEST(tests_bst_constructor, "BST<int> indirectly.")
{
    int data { 7 };
    tree::BST<int> bs_tree { data };
    ASSERT_TRUE( bs_tree.root() )
    ASSERT_TRUE( bs_tree.search(7).has_value() )
    ASSERT_EQ( bs_tree.search(7).value(), 7)
}

// std::optional can be compared, so the following makes sense.
TEST(tests_bst_constructor, "BST<std::optional<int>> with value directly.")
{
    tree::BST<std::optional<int>> bs_tree { 7 };
    ASSERT_TRUE( bs_tree.root() )
    ASSERT_TRUE( bs_tree.search(7).has_value() )
    ASSERT_EQ( bs_tree.search(7).value().value(), 7)
}
TEST(tests_bst_constructor, "BST<std::optional<int>> with value indirectly.")
{
    int data { 7 };
    tree::BST<std::optional<int>> bs_tree { data };
    ASSERT_TRUE( bs_tree.root() )
    ASSERT_TRUE( bs_tree.search(7).has_value() )
    ASSERT_EQ( bs_tree.search(7).value().value(), 7)
}
TEST(tests_bst_constructor, "BST<std::optional<int>> without value directly.")
{
    // Here we must use std::nullopt, because constructor with no arguments is forbidden.
    tree::BST<std::optional<int>> bs_tree { std::nullopt };
    ASSERT_TRUE( bs_tree.root() )
    ASSERT_TRUE( bs_tree.search(std::nullopt).has_value() )
    ASSERT_FALSE( bs_tree.search(std::nullopt).value().has_value() )
}

TEST(tests_bst_constructor, "Using struct C_Data in BST<C_Data> directly.")
{
    tree::BST<C_Data> bs_tree { 2, "Fany" };
    ASSERT_EQ( tree::count_nodes(bs_tree.root()), 1)
    ASSERT_EQ( tree::height(bs_tree.root()), 1)
    ASSERT_TRUE( bs_tree.search({2, "Fany"}).has_value() )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().number, 2 )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().text, "Fany" )
}
TEST(tests_bst_constructor, "Using struct C_Data in BST<C_Data> directly by implicit construction.")
{
    tree::BST<C_Data> bs_tree { {2, "Fany"} };
    ASSERT_EQ( tree::count_nodes(bs_tree.root()), 1)
    ASSERT_EQ( tree::height(bs_tree.root()), 1)
    ASSERT_TRUE( bs_tree.search({2, "Fany"}).has_value() )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().number, 2 )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().text, "Fany" )
}
TEST(tests_bst_constructor, "Using struct C_Data in BST<C_Data> indirectly.")
{
    C_Data data { 2, "Fany" };
    tree::BST<C_Data> bs_tree { data };
    ASSERT_EQ( tree::count_nodes(bs_tree.root()), 1)
    ASSERT_EQ( tree::height(bs_tree.root()), 1)
    ASSERT_TRUE( bs_tree.search({2, "Fany"}).has_value() )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().number, 2 )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().text, "Fany" )
}

struct C_SData
{
    int x;
    auto operator<=>(const C_SData& other) const
    {
        return x <=> other.x;
    }
    bool operator==(const C_SData& other) const
    {
        return x == other.x;
    }
};

TEST(tests_bst_constructor, "Using struct C_SData in BST<C_SData> directly.")
{
    tree::BST<C_SData> bs_tree { 2 };
    ASSERT_EQ( tree::count_nodes(bs_tree.root()), 1)
    ASSERT_EQ( tree::height(bs_tree.root()), 1)
    ASSERT_TRUE( bs_tree.search({2}).has_value() )
    ASSERT_EQ( bs_tree.search({2}).value().x, 2 )
}


// TO DO: construction from a vector


/*
    Test various construction of AVL
*/
ts::Suite tests_avl_constructor { "Testing various construction of AVL." };

TEST(tests_avl_constructor, "Empty AVL creation.")
{
    tree::AVL<int> tree_0;
    tree::AVL<int> tree_1 {};
    ASSERT_FALSE( tree_0.root() )
    ASSERT_FALSE( tree_1.root() )
    tree::AVL<C_Data> tree_2 {};
    tree::AVL<C_NData> tree_3 {};
    tree::AVL<C_DData> tree_4 {};
    ASSERT_FALSE( tree_2.root() )
    ASSERT_FALSE( tree_3.root() )
    ASSERT_FALSE( tree_4.root() )
}

TEST(tests_avl_constructor, "AVL<int> directly.")
{
    tree::AVL<int> bs_tree { 7 };
    ASSERT_TRUE( bs_tree.root() )
    ASSERT_TRUE( bs_tree.search(7).has_value() )
    ASSERT_EQ( bs_tree.search(7).value(), 7)

}
TEST(tests_avl_constructor, "AVL<int> indirectly.")
{
    int data { 7 };
    tree::AVL<int> bs_tree { data };
    ASSERT_TRUE( bs_tree.root() )
    ASSERT_TRUE( bs_tree.search(7).has_value() )
    ASSERT_EQ( bs_tree.search(7).value(), 7)
}

// std::optional can be compared, so the following makes sense.
TEST(tests_avl_constructor, "AVL<std::optional<int>> with value directly.")
{
    tree::AVL<std::optional<int>> bs_tree { 7 };
    ASSERT_TRUE( bs_tree.root() )
    ASSERT_TRUE( bs_tree.search(7).has_value() )
    ASSERT_EQ( bs_tree.search(7).value().value(), 7)
}
TEST(tests_avl_constructor, "AVL<std::optional<int>> with value indirectly.")
{
    int data { 7 };
    tree::AVL<std::optional<int>> bs_tree { data };
    ASSERT_TRUE( bs_tree.root() )
    ASSERT_TRUE( bs_tree.search(7).has_value() )
    ASSERT_EQ( bs_tree.search(7).value().value(), 7)
}
TEST(tests_avl_constructor, "AVL<std::optional<int>> without value directly.")
{
    // Here we must use std::nullopt, because constructor with no arguments is forbidden.
    tree::AVL<std::optional<int>> bs_tree { std::nullopt };
    ASSERT_TRUE( bs_tree.root() )
    ASSERT_TRUE( bs_tree.search(std::nullopt).has_value() )
    ASSERT_FALSE( bs_tree.search(std::nullopt).value().has_value() )
}

TEST(tests_avl_constructor, "Using struct C_Data in AVL<C_Data> directly.")
{
    tree::AVL<C_Data> bs_tree { 2, "Fany" };
    ASSERT_EQ( tree::count_nodes(bs_tree.root()), 1)
    ASSERT_EQ( tree::height(bs_tree.root()), 1)
    ASSERT_TRUE( bs_tree.search({2, "Fany"}).has_value() )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().number, 2 )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().text, "Fany" )
}
TEST(tests_avl_constructor, "Using struct C_Data in AVL<C_Data> directly by implicit construction.")
{
    tree::AVL<C_Data> bs_tree { {2, "Fany"} };
    ASSERT_EQ( tree::count_nodes(bs_tree.root()), 1)
    ASSERT_EQ( tree::height(bs_tree.root()), 1)
    ASSERT_TRUE( bs_tree.search({2, "Fany"}).has_value() )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().number, 2 )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().text, "Fany" )
}
TEST(tests_avl_constructor, "Using struct C_Data in AVL<C_Data> indirectly.")
{
    C_Data data { 2, "Fany" };
    tree::AVL<C_Data> bs_tree { data };
    ASSERT_EQ( tree::count_nodes(bs_tree.root()), 1)
    ASSERT_EQ( tree::height(bs_tree.root()), 1)
    ASSERT_TRUE( bs_tree.search({2, "Fany"}).has_value() )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().number, 2 )
    ASSERT_EQ( bs_tree.search({2, "Fany"}).value().text, "Fany" )
}

TEST(tests_avl_constructor, "Using struct C_SData in AVL<C_SData> directly.")
{
    tree::AVL<C_SData> bs_tree { 2 };
    ASSERT_EQ( tree::count_nodes(bs_tree.root()), 1)
    ASSERT_EQ( tree::height(bs_tree.root()), 1)
    ASSERT_TRUE( bs_tree.search({2}).has_value() )
    ASSERT_EQ( bs_tree.search({2}).value().x, 2 )
}
