/*
    General tests of AVL

    Insertion -> tree must stay balanced
              -> inserted key is in the tree

    Deletion -> tree must stay balanced
             -> deleted key must not be in the tree, unless it was there multiple times!

*/
#pragma once

#include <random>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

#include "..\lib\suite.hpp"
#include "..\..\include\avl.hpp"


ts::Suite tests_AVL { "AVL Binary Search Tree" };

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
TEST(tests_AVL, "Tree stays balanced during insertion.")
{
    constexpr int THREADS { 8 };
    constexpr int ITERATIONS { 1000 };
    constexpr int ITERATIONS_PER_THREAD { ITERATIONS / THREADS };
    std::vector<std::string> log;
    std::vector<std::jthread> threads; // Can use array?
    for ( size_t i {0}; i < THREADS; ++i )
        threads.emplace_back(test_add_, ITERATIONS_PER_THREAD, std::ref(log));
    // Log the log vector into a file
    ASSERT
    (
        log.empty(),
        "Balance broken during insertion."
    )
}

void test_remove_(int iterations, std::vector<std::tuple<std::string, std::string>>& log)
{
    const int COUNT { 1000 };
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
TEST(tests_AVL, "Tree stays balanced during deletion.")
{
    constexpr int THREADS { 8 };
    constexpr int ITERATIONS { 1000 };
    constexpr int ITERATIONS_PER_THREAD { ITERATIONS / THREADS };
    std::vector<std::tuple<std::string, std::string>> log;
    std::vector<std::jthread> threads; // Can use array?
    for ( size_t i {0}; i < THREADS; ++i )
        threads.emplace_back(test_remove_, ITERATIONS_PER_THREAD, std::ref(log));
    // Log the log vector into a file
    ASSERT
    (
        log.empty(),
        "Balance broken during deletion."
    )
}

tree::AVL<int> set_up_avl()
{
    tree::AVL<int> search_tree;
    search_tree.add(7);
    search_tree.add(2);
    search_tree.add(56);
    search_tree.add(8);
    search_tree.add(23);
    search_tree.add(3);
    return search_tree;
}

void bst_property_(tree::AVL<int>& search_tree)
{
    int value { INT_MIN };
    for ( auto it {search_tree.begin()}; it != search_tree.end(); ++it)
    {
        ASSERT
        (
            *it >= value,
            "Key in AVL not in order."
        )
        value = *it;
    }
}


/*
    THIS IS NOT STRICTLY TRUE!
*/
TEST(tests_AVL, "Adding key preserves the BST property.")
{
    auto search_tree { set_up_avl() };
    search_tree.add(666);
    bst_property_(search_tree);
}

TEST(tests_AVL, "Removing key preserves the BST property.")
{
    auto search_tree { set_up_avl() };
    search_tree.remove(23);
    bst_property_(search_tree);
}

/*
    extract min and extract max
*/
TEST(tests_AVL, "Extracting maximum preserves balance.")
{
    auto search_tree { set_up_avl() };
    search_tree.extract_max();
    ASSERT
    (
        tree::is_balanced(search_tree.root()),
        "extract_max doesn't preserves balance."
    )
}

TEST(tests_AVL, "Extracting minimum preserves balance.")
{
    auto search_tree { set_up_avl() };
    search_tree.extract_min();
    ASSERT
    (
        tree::is_balanced(search_tree.root()),
        "extract_min doesn't preserves balance."
    )
}

/*
    extract min node and extract max node
*/
TEST(tests_AVL, "Extracting maximum node preserves balance.")
{
    auto search_tree { set_up_avl() };
    search_tree.extract_max_node();
    ASSERT
    (
        tree::is_balanced(search_tree.root()),
        "extract_max_node doesn't preserves balance."
    )
}

TEST(tests_AVL, "Extracting minimum node preserves balance.")
{
    auto search_tree { set_up_avl() };
    search_tree.extract_min_node();
    ASSERT
    (
        tree::is_balanced(search_tree.root()),
        "extract_min_node doesn't preserves balance."
    )
}
