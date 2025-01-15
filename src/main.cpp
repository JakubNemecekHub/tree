#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#include "linked.hpp"
#include "bst.hpp"
#include "types.hpp"


void print_one_more(std::optional<int> data)
{
    std::cout << data.value() + 1 << ' ';
}



std::ostream& operator<<(std::ostream& os, const My_Data& obj)
{
    return os << "(" << obj.key << " " << obj.name << ")\n";
}

int main(int argc, char* argv[])
{

    // // Methods of Initialization.
    // My_Data my_data {6, "Max"};
    // auto root_0 { std::make_unique<tree::Node<My_Data>>(my_data)};              // Pass existing object. -> This Creates an object an copies it once.
    //                                                                             // Should it move the object? No, we should be explicit about that.
    // My_Data my_data_1 {10, "Bady"};
    // auto root_1 { std::make_unique<tree::Node<My_Data>>(std::move(my_data_1))}; // Pass existing object. -> This Creates an object an moves it once.
    // auto root_2 { std::make_unique<tree::Node<My_Data>>(My_Data{12, "Fany"})};  // Create object during initialization. (What's the proper name for this?) -> This Creates an object and moves it.
    //                                                                             // No reason to use this. Prefer the following method.
    // auto root_3 { std::make_unique<tree::Node<My_Data>>(2, "Fany") };           // Use variadic template to perfect forward parameters. -> Object created in place. Hooray!
    // auto root_4 { std::make_unique<tree::Node<My_Data>>()};                     // Node with no data. Note, that passing std::nullopt doesn't work. -> No object

    // // Methods of Creation.
    // auto root { std::make_unique<tree::Node<My_Data>>(2, "Fany") }; // In place.
    // auto& left_child { root->left(My_Data{4, "Sandy"}) };           // This creates a copy. No reason to use.
    // auto& right_child { root->right(1, "Fig") };                    // In place.
    // auto& empty_node { left_child->left() };
    // My_Data bady {11, "Bady"};
    // left_child->right(bady);                                        // Copies twice :(
    // My_Data max {6, "Max"};
    // left_child->left(std::move(max));

    // tree::print(root);

    /*
        PARSE ARGUMENTS
    */
    // if ( argc < 2 )
    // {
    //     std::cerr << "Please provide file name.\n";
    //     return 1;
    // }
    // else if ( argc > 2 )
    // {
    //     std::cerr << "Too many arguments.\n";
    //     return 1;
    // }
    // std::string path { argv[1] };

    /*
        SERIALIZE TREE
    */
    // auto root { std::make_unique<tree::Node<int>>(1) };
    // auto& it { root->left(2) };
    // it->left(4);
    // it->right(5);
    // auto& another_it { root->right(3) };
    // another_it->left(6);
    // tree::print(root);
    // std::ofstream out { path };
    // if ( !out.is_open() )
    // {
    //     std::cerr << "Cannot open file " << path << '\n';
    //     return 1;
    // }
    // tree::serialize(root, out);
    // out.close();

    /*
        DESERIALIZE AND USE A TREE
    */
    // std::ifstream in { path };
    // if ( !in.is_open() )
    // {
    //     std::cerr << "Cannot open file " << path << '\n';
    //     return 1;
    // }
    // auto root { tree::deserialize<int>(in) };
    // in.close();
    // tree::print(root);

    // auto f_print = [](const auto& data){ std::cout << data.value() << ' '; };

    // std::cout << "In    Order: "; tree::in_order(root, f_print);    std::cout << '\n';
    // std::cout << "Pre   Order: "; tree::pre_order(root, f_print);   std::cout << '\n';
    // std::cout << "Post  Order: "; tree::post_order(root, f_print);  std::cout << '\n';
    // std::cout << "Level Order: "; tree::level_order(root, f_print); std::cout << '\n';

    // Just a test that traversal can handle an empty tree.
    // Node<double>* t { nullptr };
    // in_order(t, f_print);

    // std::cout << "HEIGHT: " << tree::height(root) << '\n';
    // std::cout << "NODES: "  << tree::count_nodes(root) << '\n';

    // std::cout << std::boolalpha
    //           << "FULL: "     << tree::is_full(root)     << '\n'
    //           << "COMPLETE: " << tree::is_complete(root) << '\n'
    //           << "PERFECT: "  << tree::is_perfect(root)  << '\n'
    //           << "BALANCED: " << tree::is_balanced(root) << '\n'
    //           << std::noboolalpha;

    // const int KEY_NORMAL { 5 };
    // auto result_normal { tree::search(root, KEY_NORMAL) };
    // std::cout << "Looking for " << KEY_NORMAL << ", found ";
    // if ( result_normal.has_value() ) std::cout << "node with value " << result_normal.value() << ".\n";
    // else                             std::cout << "nothing.\n";

    /*
        BINARY SEARCH TREE
    */
    // tree::BST<int> search_tree {70};
    // search_tree.add(60);
    // search_tree.add(80);
    // search_tree.add(50);
    // search_tree.add(70);
    // search_tree.add(55);
    // search_tree.add(85);
    // search_tree.add(83);
    // search_tree.add(87);
    // search_tree.add(84);
    // search_tree.add(86);

    // std::cout << "in Order traversal of Binary Search Tree prints its elements ordered:\n";
    // tree::in_order<int>(search_tree, f_print);

    // std::cout << "\n===================================================\n";
    // tree::print(search_tree);
    // std::cout << "\n===================================================\n";

    // const int KEY { 55 };
    // auto result { search_tree.search(KEY) };
    // std::cout << "Searched for " << KEY << " and got ";
    // if ( result.has_value() )
    //     std::cout << result.value() << '\n';
    // else
    //     std::cout << "nothing\n";

    // auto maximum { search_tree.max() };
    // std::cout << "Maximum value is: ";
    // if ( maximum.has_value() ) std::cout << maximum.value() << '\n';
    // else                       std::cout << "there is no maximum\n";
    // auto minimum { search_tree.min() };
    // std::cout << "Minimum value is: ";
    // if ( minimum.has_value() ) std::cout << minimum.value() << '\n';
    // else                       std::cout << "there is no minimum\n";

    // auto extracted_max_node { search_tree.extract_max_node() };
    // std::cout << "Extracted ";
    // if ( extracted_max_node != nullptr )
    //     std::cout << "a node with value " << extracted_max_node->data.value() << '\n';
    // else
    //     std::cout << "nothing\n";
    // std::cout << "\n===================================================\n";
    // std::cout << "After extraction:\n";
    // tree::print(search_tree);
    // std::cout << "\n===================================================\n";

    // auto extracted_min_node { search_tree.extract_min_node() };
    // std::cout << "Extracted ";
    // if ( extracted_min_node != nullptr )
    //     std::cout << "a node with value " << extracted_min_node->data.value() << '\n';
    // else
    //     std::cout << "nothing\n";
    // std::cout << "\n===================================================\n";
    // std::cout << "After extraction:\n";
    // tree::print(search_tree);
    // std::cout << "\n===================================================\n";

    // auto extracted_max_value { search_tree.extract_max() };
    // std::cout << "Extracted ";
    // if  ( extracted_max_value.has_value() )
    //     std::cout << "value " << extracted_max_value.value() << '\n';
    // else
    //     std::cout << "nothing\n";
    // std::cout << "\n===================================================\n";
    // std::cout << "After extraction:\n";
    // tree::print(search_tree);
    // std::cout << "\n===================================================\n";

    // auto extracted_min_value { search_tree.extract_min() };
    // std::cout << "Extracted ";
    // if  ( extracted_min_value.has_value() )
    //     std::cout << "a node with value " << extracted_min_value.value() << '\n';
    // else
    //     std::cout << "nothing\n";
    // std::cout << "\n===================================================\n";
    // std::cout << "After extraction:\n";
    // tree::print(search_tree);
    // std::cout << "\n===================================================\n";

    // // Deletion
    // tree::in_order<int>(search_tree, f_print); std::cout << '\n';
    // search_tree.remove(80);
    // tree::in_order<int>(search_tree, f_print); std::cout << '\n';
    // std::cout << "\n===================================================\n";
    // tree::print(search_tree);
    // std::cout << "\n===================================================\n";

    /*
        BINARY SEARCH TREE
        with a struct
    */
   tree::BST<My_Data> search_tree {My_Data(2, "Fany")};
   search_tree.add(My_Data{5, "Sandy"});
   search_tree.add(My_Data(3, "Cinty"));
   search_tree.add(My_Data{1, "Fig"});
//    tree::print(search_tree);

    auto& root { search_tree.root() };
    tree::print(root);

    auto it { search_tree.extract_min_node() };
    std::cout << "\n\n\n\n" << it->data.value() << '\n';

    return 0;
}
