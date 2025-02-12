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
#include "..\..\src\avl.hpp"


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


TEST(tests_AVL, "Empty tree creation.")
{
    tree::AVL<int> search_tree;
    ASSERT
    (
        !search_tree.root(),
        "Root of empty AVL is not nullptr."
    )
}

TEST(tests_AVL, "Number of nodes in empty tree must be 0.")
{
    tree::AVL<int> search_tree;
    ASSERT
    (
        tree::count_nodes(search_tree.root()) == 0,
        "Number of nodes in empty tree is not 0."
    )
}

TEST(tests_AVL, "Height of empty tree must be 0.")
{
    tree::AVL<int> search_tree;
    ASSERT
    (
        tree::height(search_tree.root()) == 0,
        "Height of empty tree is not 0."
    )
}

TEST(tests_AVL, "Non-empty tree creation.")
{
    tree::AVL<int> search_tree { 7 };
    ASSERT
    (
        search_tree.root(),
        "Root of non-empty AVL is nullptr."
    )
}

TEST(tests_AVL, "Adding to empty tree.")
{
    tree::AVL<int> search_tree;
    search_tree.add(7);
    ASSERT
    (
        search_tree.root(),
        "Root of previously empty AVL is nullptr after adding a value."

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

TEST(tests_AVL, "AVL fullfills the BST property.")
{
    auto search_tree { set_up_avl() };
    bst_property_(search_tree);
}

TEST(tests_AVL, "Result of a search for existing key has a valid value.")
{
    auto search_tree { set_up_avl() };
    ASSERT
    (
        search_tree.search(56).has_value(),
        "Search for existing key doesn't have value."
    )
}
TEST(tests_AVL, "Result of a search for existing key has a correct value.")
{
    auto search_tree { set_up_avl() };
    ASSERT
    (
        search_tree.search(56).value() == 56,
        "Search returns wrong value."
    )
}

TEST(tests_AVL, "Result of a search for non-existing key is std::nullopt.")
{
    auto search_tree { set_up_avl() };
    ASSERT
    (
        search_tree.search(222) == std::nullopt,
        "Search for non existing value doesn't return std::nullopt."
    )
}

// THIS MIGHT NOT BE TRUE!
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

TEST(tests_AVL, "Removing existing key returns true.")
{
    auto search_tree { set_up_avl() };
    ASSERT
    (
        search_tree.remove(23),
        "Removing existing key returned false."
    )

}
TEST(tests_AVL, "Removed key is no longer in AVL.")
{
    auto search_tree { set_up_avl() };
    search_tree.remove(23);
    ASSERT
    (
        search_tree.search(23) == std::nullopt,
        "Removing existing key didn't remove it."
    )
}

TEST(tests_AVL, "Removing non-existing key returns false.")
{
    auto search_tree { set_up_avl() };
    ASSERT
    (
        !search_tree.remove(222),
        "Removing non-existing key returned true."
    )
}

/*
    min and max
*/
TEST(tests_AVL, "max returns the maximum value.")
{
    auto search_tree { set_up_avl() };
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
TEST(tests_AVL, "Maximum of empty AVL is std::nullopt.")
{
    tree::AVL<int> search_tree;
    ASSERT
    (
        search_tree.max() == std::nullopt,
        "Maximum of empty BTS is not std::nullopt."
    )
}


TEST(tests_AVL, "min returns the minimum value.")
{
    auto search_tree { set_up_avl() };
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
TEST(tests_AVL, "Minimum of empty AVL is std::nullopt.")
{
    tree::AVL<int> search_tree;
    ASSERT
    (
        search_tree.max() == std::nullopt,
        "Minimum of empty BTS is not std::nullopt."
    )
}

/*
    extract min and extract max
*/
TEST(tests_AVL, "Extracted maximum is larger that remaining keys.")
{
    auto search_tree { set_up_avl() };
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
TEST(tests_AVL, "Extracted maximum is removed from tree.")
{
    auto search_tree { set_up_avl() };
    auto maximum { search_tree.extract_max() };
    ASSERT
    (
        search_tree.search(maximum.value()) == std::nullopt,
        "extract_max doesn't remove extracted key from tree."
    )
}
TEST(tests_AVL, "Extracted maximum from empty tree is std::nullopt.")
{
    tree::AVL<int> search_tree;
    ASSERT
    (
        search_tree.extract_max() == std::nullopt,
        "extract_max extracts something from an empty tree."
    )
}

TEST(tests_AVL, "Extracted minimum is smaller that remaining keys.")
{
    auto search_tree { set_up_avl() };
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
TEST(tests_AVL, "Extracted minimum is removed from tree.")
{
    auto search_tree { set_up_avl() };
    auto minimum { search_tree.extract_min() };
    ASSERT
    (
        search_tree.search(minimum.value()) == std::nullopt,
        "extract_min doesn't remove extracted key from tree."
    )
}
TEST(tests_AVL, "Extracted minimum from empty tree is std::nullopt.")
{
    tree::AVL<int> search_tree;
    ASSERT
    (
        search_tree.extract_min() == std::nullopt,
        "extract_min extracts something from an empty tree."
    )
}

/*
    extract min node and extract max node
*/
TEST(tests_AVL, "Extracted maximum node is larger that remaining keys.")
{
    auto search_tree { set_up_avl() };
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
TEST(tests_AVL, "Extracted maximum node is removed from tree.")
{
    auto search_tree { set_up_avl() };
    auto maximum { search_tree.extract_max_node() };
    ASSERT
    (
        search_tree.search(maximum->data) == std::nullopt,
        "extract_max_node doesn't remove extracted key from tree."
    )
}
TEST(tests_AVL, "Extracted maximum node from empty tree is nullptr.")
{
    tree::AVL<int> search_tree;
    ASSERT
    (
        !search_tree.extract_max_node(),
        "extract_max_node extracts something from an empty tree."
    )
}

TEST(tests_AVL, "Extracted minimum node is smaller that remaining keys.")
{
    auto search_tree { set_up_avl() };
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
TEST(tests_AVL, "Extracted minimum node is removed from tree.")
{
    auto search_tree { set_up_avl() };
    auto minimum { search_tree.extract_min_node() };
    ASSERT
    (
        search_tree.search(minimum->data) == std::nullopt,
        "extract_min_node doesn't remove extracted key from tree."
    )
}
TEST(tests_AVL, "Extracted minimum node from empty tree is nullptr.")
{
    tree::AVL<int> search_tree;
    ASSERT
    (
        !search_tree.extract_min_node(),
        "extract_min_node extracts something from an empty tree."
    )
}


