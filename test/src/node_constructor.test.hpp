/*
    Test various construction of Node
*/
#pragma once

#include <optional>
#include <string>

#include "..\lib\suite.hpp"
#include "..\..\include\linked.hpp"
#include "..\..\include\bst.hpp"


ts::Suite tests_node_constructor { "Testing various construction of Node." };

/*
    tree::Node
*/
// TEST(tests_node_constructor, "Empty Node.")
// {
//     tree::Node<int> root;
//     tree::Node<int> root {};
//     // This is forbidden. What value would data hold anyway!?
// }
/*
    Default constructible type in Node
*/
struct Data
{
    int number; std::string text;
};
struct NData
{
    int number; std::string text;
    NData(int _number, std::string _text)
        : number{_number}, text{_text} {}
};
struct DData
{
    int number; std::string text;
    DData() : number{0}, text{"Name"} {}
};

TEST(tests_node_constructor, "Creating empty node with default constructible data.")
{
    // // Data has no default constructor
    tree::Node<Data> root_0;  // Oh no. This works :( -> int left uninitialized, string value initialized ""
    tree::Node<Data> root_1 {};  // This also works :( -> both fields value initialized 0 and ""
    // tree::Node<NData> root_2;
    // tree::Node<NData> root_3 {};
    tree::Node<DData> root_2;
    tree::Node<DData> root_3 {};
    /*
        Overview:
        Data has an implicit default constructor.
        Because NData defines a constructor that takes some parameters, the implicit default constructor is not created
        DData has explicit default constructor.

    */
}

TEST(tests_node_constructor, "Node<int> directly.")
{
    tree::Node<int> root { 7 };
}
TEST(tests_node_constructor, "Node<int> indirectly.")
{
    int data { 7 };
    tree::Node<int> root { data };
}

TEST(tests_node_constructor, "Node<std::optional<int>> with value directly.")
{
    tree::Node<std::optional<int>> root { 7 };
    ASSERT_TRUE( root.data.has_value() )
    ASSERT_EQ( root.data.value(), 7 )
}
TEST(tests_node_constructor, "Node<std::optional<int>> with value indirectly.")
{
    int data { 7 };
    tree::Node<std::optional<int>> root { data };
    ASSERT_TRUE( root.data.has_value() )
    ASSERT_EQ( root.data.value(), data )
}
TEST(tests_node_constructor, "Node<std::optional<int>> without value directly.")
{
    // Here we must use std::nullopt, because constructor with no arguments is forbidden.
    tree::Node<std::optional<int>> root { std::nullopt };
    ASSERT_FALSE( root.data.has_value() )
}

TEST(tests_node_constructor, "Using struct Data in Node<Data> directly.")
{
    tree::Node<Data> root { 2, "Fany" };
    ASSERT_EQ( root.data.number, 2)
    ASSERT_EQ( root.data.text, "Fany" )
}
TEST(tests_node_constructor, "Using struct Data in Node<Data> directly by implicit construction.")
{
    tree::Node<Data> root { {2, "Fany"} };
    ASSERT_EQ( root.data.number, 2)
    ASSERT_EQ( root.data.text, "Fany" )
}
TEST(tests_node_constructor, "Using struct Data in Node<Data> indirectly.")
{
    Data data { 2, "Fany" };
    tree::Node<Data> root { data };
    ASSERT_EQ( root.data.number, data.number )
    ASSERT_EQ( root.data.text, data.text )
}
