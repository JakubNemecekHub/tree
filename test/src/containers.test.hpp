/*
    Test of Binary Tree inside STL containers
*/
#pragma once

#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>

#include <string>

#include "..\lib\ts\suite.hpp"
#include "..\..\include\linked.hpp"


ts::Suite tests_containers { "Binary Tree in STL containers" };

/*
    Array

    We must use a default constructible type.
*/
struct DefaultData
{
    int number; std::string text;
    DefaultData(int _number = 0) : number{_number}, text{"Name"} {}
};

TEST(tests_containers, "Binary Tree in an array.")
{
    std::array<tree::Node<DefaultData>, 2> arr;
    ASSERT_FALSE( arr.empty() );
    ASSERT_EQ( arr.size(), 2 )
    tree::Node<DefaultData> node_1 { 7 };
    arr.at(1) = std::move(node_1);
}

/*
    Vector
*/
TEST(tests_containers, "Binary Tree in a vector.")
{
    std::vector<tree::Node<int>> vec_1;
    ASSERT_TRUE( vec_1.empty() )
    vec_1.emplace_back(7);
    ASSERT_FALSE( vec_1.empty() )
    ASSERT_EQ( vec_1.size(), 1 )
    vec_1.emplace_back(8);
    ASSERT_EQ( vec_1.size(), 2 )

    std::vector<tree::Node<int>> vec_2;
    ASSERT_TRUE( vec_2.empty() )
    tree::Node<int> node_1 { 7 };
    vec_2.push_back(std::move(node_1));
    ASSERT_FALSE( vec_2.empty() )
    ASSERT_EQ( vec_2.size(), 1 )
    tree::Node<int> node_2 { 8 };
    vec_2.push_back(std::move(node_2));
    ASSERT_EQ( vec_2.size(), 2 )

    vec_2.reserve(10);

    auto& node_1_again { vec_2.at(0) };
    ASSERT_EQ( node_1_again.data, 7 )
    ASSERT_EQ( vec_2.size(), 2 )

    /*
        The node stays in the vector after a "move".
    */
    tree::Node<int> node_2_again { std::move(vec_2.at(1)) };
    // vec_2.pop_back();
    vec_2.erase(vec_2.begin() + 2);
    ASSERT_EQ( node_2_again.data, 8 )
    ASSERT_EQ( vec_2.size(), 1 )

    // std::vector<tree::Node<int>> vec_3 { tree::Node<int>{1}, tree::Node<int>{2} };  // This wants to copy nodes

}

/*
    Queue

    Normal queue should work. Priority queue cannot work with move only types.
*/
TEST(tests_containers, "Binary Tree in a  queue.")
{
    std::queue<tree::Node<int>> q;
    q.emplace(7);
    tree::Node<int> node { std::move(q.front()) };
}

TEST(tests_containers, "Priority queue.")
{
    std::priority_queue<tree::Node<int>, std::vector<tree::Node<int>>> pq;
    pq.emplace(7);
    auto& n = pq.top();
    ASSERT_EQ( n.data, 7 )
    pq.pop();
    ASSERT_EQ( n.data, 7 )
    // auto node { std::move(pq.top()) };  // Why cannot we do this?
}
