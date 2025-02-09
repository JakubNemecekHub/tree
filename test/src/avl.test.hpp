#pragma once
/*
    General tests of AVL

    Insertion -> tree must stay balanced
              -> inserted key is in the tree

    Deletion -> tree must stay balanced
             -> deleted key must not be in the tree, unless it was there multiple times!

*/

#include <random>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

#include "..\..\src\avl.hpp"

std::vector<int> generate_numbers(int count)
{
    unsigned int seed { std::chrono::system_clock::now().time_since_epoch().count() };
    std::default_random_engine generator{seed};
    const int MIN {   1 };
    const int MAX { 100 };
    std::uniform_int_distribution<int> distribution{MIN, MAX};
    std::vector<int> vec;
    vec.reserve(count);
    for ( int i {0}; i < count; ++i) vec.push_back(distribution(generator));
    return vec;
}

template<typename T>
void print_v(const std::vector<T>& vec)
{
    for (const auto& item : vec) std::cout << item << ", ";
    std::cout << '\n';
}

template<typename T>
// add concept that T can be cast to string
std::string v_to_string(const std::vector<T>& vec)
{
    std::string res;
    for (const auto item : vec) res += std::to_string(item) + ", ";
    return res;
}

void test_add_(int iterations, std::vector<std::string>& log)
{
    constexpr int COUNT { 1000 };
    for ( int i {0}; i < iterations; ++i)
    {
        auto numbers { generate_numbers(COUNT) };
        tree::AVL<int> search_tree;
        for ( auto number : numbers ) search_tree.add(number);
        if ( !tree::is_balanced(search_tree.root()) )
            log.emplace_back(v_to_string(numbers));
    }
}
void test_add()
{
    constexpr int THREADS { 8 };
    constexpr int ITERATIONS { 1000 };
    constexpr int ITERATIONS_PER_THREAD { ITERATIONS / THREADS };
    std::vector<std::string> log;
    std::vector<std::jthread> threads; // Can use array?
    for ( size_t i {0}; i < THREADS; ++i )
        threads.emplace_back(test_add_, ITERATIONS_PER_THREAD, std::ref(log));
    if ( !log.empty() ) throw std::runtime_error("Balance broken during insertion.");
    // Log the log vector into a file
}

void test_remove_(int iterations, std::vector<std::tuple<std::string, std::string>>& log)
{
    const int COUNT { 10 };
    const int DELETION_INDEX { 5 }; // TO DO: Choose random index
    for ( int i {0}; i < iterations; ++i)
    {
        auto numbers      { generate_numbers(COUNT)    };
        int to_be_deleted { numbers.at(DELETION_INDEX) };
        tree::AVL<int> search_tree;
        for ( auto number : numbers ) search_tree.add(number);
        search_tree.remove(to_be_deleted);
        if ( !tree::is_balanced(search_tree.root()) )
        {
            // log.emplace_back(std::to_string(to_be_deleted), v_to_string(numbers));
        }
    }
}
void test_remove()
{
    constexpr int THREADS { 8 };
    constexpr int ITERATIONS { 1000 };
    constexpr int ITERATIONS_PER_THREAD { ITERATIONS / THREADS };
    std::vector<std::tuple<std::string, std::string>> log;
    std::vector<std::jthread> threads; // Can use array?
    for ( size_t i {0}; i < THREADS; ++i )
        threads.emplace_back(test_remove_, ITERATIONS_PER_THREAD, std::ref(log));
    if ( !log.empty() ) throw std::runtime_error("Balance broken during deletion.");
    // Log the log vector into a file
}

