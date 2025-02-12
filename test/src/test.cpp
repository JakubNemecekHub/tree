#include "..\lib\tester.hpp"

#include "_tests.hpp"

int main()
{

    ts::Tester tester { "Test suites of Binary Tree and its variants." };
    tester.add(tests_BT, "tests_BT");
    tester.add(tests_BST, "tests_BST");
    tester.add(tests_AVL, "tests_AVL");
    tester.run();

    return 0;
}
