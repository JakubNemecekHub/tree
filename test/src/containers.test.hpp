/*
    Test of Binary Tree inside STL containers
*/
#pragma once

#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>

#include "..\lib\ts\suite.hpp"
#include "..\..\include\linked.hpp"


ts::Suite tests_containers { "Binary Tree in STL containers" };

TEST(tests_containers, "Queue")
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
