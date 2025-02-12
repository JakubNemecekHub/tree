#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <sstream>


namespace ts
{

// ANSI escape sequences for colours.
constexpr std::string RED   { "\033[31m" };
constexpr std::string GREEN { "\033[32m" };
constexpr std::string CYAN  { "\033[36m" };
constexpr std::string RESET { "\033[0m"  };


class Suite
{
public:

    using test_function_t = std::function<void()>;

private:

    std::string name_;
    std::vector<std::pair<std::string, test_function_t>> tests_;

public:

    Suite(const std::string& name = "Test Suite")   // TO DO check why const &
        : name_{name} {}

    void register_test(const std::string& message, test_function_t test)
    {
        tests_.emplace_back(message, test);
    }

    void run()
    {
        int passed { 0 };
        int failed { 0 };
        std::cout << "Running tests from " << CYAN << name_ << RESET <<'\n';
        for ( const auto [message, test] : tests_ )
        {
            try
            {
                test();
                std::cout << GREEN << "[PASSED] " << RESET << message << '\n';
                ++passed;
            }
            catch(const std::exception& e)
            {
                std::cout << RED << "[FAILED] " << RESET << message << e.what() << '\n';
                ++failed;
            }
            catch(...)
            {
                std::cout << "[FAILED] " << message << ": unknown error\n";
                ++failed;
            }
        }
        std::cout << "Suite Summary: " << passed << " passed, " << failed << " failed.\n";
        std::cout << "==================================\n\n";
    }

};

#define CONCAT_INNER(a, b) a ## b
#define CONCAT(a, b) CONCAT_INNER(a, b)
// Fo the indirection here see https://stackoverflow.com/questions/13301428/token-pasting-and-line/13301627#13301627
#define UNIQUE_NAME(base) CONCAT(base, __LINE__)

#define TEST(suite, message)                                          \
    void UNIQUE_NAME(TestFunction_)();                                \
    struct UNIQUE_NAME(TestRegistrar_)                                \
    {                                                                 \
        UNIQUE_NAME(TestRegistrar_)()                                 \
        {                                                             \
            suite.register_test(message, UNIQUE_NAME(TestFunction_)); \
        }                                                             \
    } UNIQUE_NAME(test_registrar_);                                   \
    void UNIQUE_NAME(TestFunction_)()

#define ASSERT(condition, message)                                           \
if ( !(condition) )                                                          \
{                                                                            \
    std::ostringstream oss;                                                  \
    oss << " [ASSERTION FAILED] " << #condition << " [MESSAGE] " << message; \
    throw std::runtime_error(oss.str());                                     \
}

}  // namespace ts
