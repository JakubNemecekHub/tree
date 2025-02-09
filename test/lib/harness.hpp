#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

// ANSI escape sequences for colours.
constexpr std::string RED   { "\033[31m" };
constexpr std::string GREEN { "\033[32m" };
constexpr std::string RESET { "\033[0m"  };

class TestSuite
{
private:

    std::vector<std::function<void()>> tests;
    int passed {0};
    int failed {0};

public:

    void add(const std::string& name, std::function<void()> test)
    {
        tests.push_back([this, name, test]()
        {
            try
            {
                test();
                std::cout << GREEN << "[PASS] " << RESET << name << '\n';
                ++passed;
            }
            catch(const std::exception& e)
            {
                std::cout << RED << "[FAILED] " << RESET << name << " [ERROR] " << e.what() << '\n';
                ++failed;
            }
            catch(...)
            {
                std::cout << "[FAIL] " << name << ": unknown error\n";
                ++failed;
            }
        });
    }

    void run()
    {
        for (const auto& test : tests) test();
        std::cout << "\nSummary: " << passed << " passed, " << failed << " failed.\n";
    }

};
