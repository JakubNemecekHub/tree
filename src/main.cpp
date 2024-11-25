#include <iostream>
#include <string>
#include <fstream>

#include "linked.hpp"

void print_one_more(std::optional<int> data)
{
    std::cout << data.value() + 1 << ' ';
}

int main(int argc, char* argv[])
{

    /*
        PARSE ARGUMENTS
    */
    if ( argc < 2 )
    {
        std::cerr << "Please provide file name.\n";
        return 1;
    }
    else if ( argc > 2 )
    {
        std::cerr << "Too many arguments.\n";
        return 1;
    }
    std::string path { argv[1] };

    /*
        SERIALIZE TREE
    */
    // Node<int>* it;
    // Node<int> root { 1 };
    // it = root.left(2);
    // it->left(4);
    // it->right(5);
    // it = root.right(3);
    // it->left(6);


    // print_tree(&root); std::cout << '\n';


    // std::ofstream out { path };
    // if ( !out.is_open() )
    // {
    //     std::cerr << "Cannot open file " << path << '\n';
    //     return 1;
    // }

    // serialize(&root, out);
    // out.close();

    /*
        DESERIALIZE AND USE A TREE
    */
    std::ifstream in { path };
    if ( !in.is_open() )
    {
        std::cerr << "Cannot open file " << path << '\n';
        return 1;
    }
    tree::Node<int>* root { tree::deserialize<int>(in) };
    in.close();
    print_tree(root);

    auto f_print = [](const auto& data){ std::cout << data.value() << ' '; };

    std::cout << "In    Order: "; in_order(root, f_print);    std::cout << '\n';
    std::cout << "Pre   Order: "; pre_order(root, f_print);   std::cout << '\n';
    std::cout << "Post  Order: "; post_order(root, f_print);  std::cout << '\n';
    std::cout << "Level Order: "; level_order(root, f_print); std::cout << '\n';

    // Just a test that traversal can handle an empty tree.
    // Node<double>* t { nullptr };
    // in_order(t, f_print);

    std::cout << "HEIGHT: " << tree::height(root) << '\n';
    std::cout << "NODES: "  << tree::count_nodes(root) << '\n';

    std::cout << std::boolalpha
              << "FULL: "     << tree::is_full(root)     << '\n'
              << "COMPLETE: " << tree::is_complete(root) << '\n'
              << "PERFECT: "  << tree::is_perfect(root)  << '\n'
              << "BALANCED: " << tree::is_balanced(root) << '\n'
              << std::noboolalpha;

    return 0;
}
