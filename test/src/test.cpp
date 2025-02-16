#include "..\lib\ts\tester.hpp"

#include "_tests.hpp"

int main()
{

    ts::Tester tester { "Test suites of Binary Tree and its variants." };
    tester.add(tests_BT, "tests_BT");
    tester.add(tests_BST, "tests_BST");
    tester.add(tests_AVL, "tests_AVL");
    tester.add(tests_node_constructor, "tests_node_constructor");
    tester.add(tests_bst_constructor, "tests_bst_constructor");
    tester.add(tests_avl_constructor, "tests_avl_constructor");
    tester.add(tests_containers, "tests_containers");
    tester.run();

    return 0;
}
