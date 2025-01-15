#pragma once

#include <iostream>
#include <string>

struct My_Data
{
    int key;
    std::string name;
    My_Data() {};
    My_Data(int key_, std::string name_)
        : key{key_}, name{name_}
    {
        std::cout << "Created " << name << ", age " << key << '\n';
    }
    My_Data(const My_Data& other)
    {
        this->key = other.key;
        this->name = other.name;
        std::cout << "Copied " << this->name << ", age " << this->key << '\n';
    }
    My_Data(My_Data&& other)
        : key{other.key}, name{std::move(other.name)}
    {
        std::cout << "Moved " << this->name << ", age " << this->key << '\n';
    }
    ~My_Data()
    {
        std::cout << "(" << name << ", " << key << ") is gone \n";
    }

    auto operator<=>(const My_Data& other) const
    {
        return key <=> other.key;
    }
};

