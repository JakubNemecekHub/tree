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

    tree::AVL<int> avl { 7 };
    avl.add(6);
    avl.add(5);
    avl.add(4);
    avl.add(3);
    avl.add(2);

    // auto n { avl.extract_max() };

    tree::print(avl.root());

    // tree::print(avl);
    // tree::in_order(avl, [](int data) {
    //     std::cout << data << ", ";
    // });

    return 0;
}
