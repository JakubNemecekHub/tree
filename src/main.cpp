#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <algorithm>
#include <ranges>


#include "linked.hpp"
#include "bst.hpp"
#include "avl.hpp"
#include "types.hpp"


int main(int argc, char* argv[])
{

    std::vector<int> data {};
    tree::AVL<int> search_tree { data };
    tree::print(search_tree.root());

    // auto n { avl.extract_max() };


    // tree::print(avl);
    // tree::in_order(avl, [](int data) {
    //     std::cout << data << ", ";
    // });

    return 0;
}
