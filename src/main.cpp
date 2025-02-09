#include <iostream>
#include <string>
#include <memory>
#include <vector>


#include "linked.hpp"
#include "avl.hpp"
#include "types.hpp"


void print_one_more(std::optional<int> data)
{
    std::cout << data.value() + 1 << ' ';
}

int main(int argc, char* argv[])
{

    // std::vector<int> values {99, 39, 30, 35, 69, 24, 36, 53, 53, 2};
    // tree::AVL<int> search_tree {};
    // for ( auto value : values) search_tree.add(value);
    // std::cout << "\n=====================================================================\n";
    // tree::print(search_tree);
    // std::cout << "BALANCED: " << std::boolalpha << tree::is_balanced(search_tree.root()) << '\n';
    // std::cout << "\n=====================================================================\n";
    // int to_be_deleted { 24 };
    // std::cout << "Deleting: " << to_be_deleted << '\n';
    // search_tree.remove(to_be_deleted);
    // std::cout << "\n=====================================================================\n";
    // tree::print(search_tree);
    // std::cout << "\n=====================================================================\n";
    // std::cout << "BALANCED: " << std::boolalpha << tree::is_balanced(search_tree.root()) << '\n';

    return 0;
}
