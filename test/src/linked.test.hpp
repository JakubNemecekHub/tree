#pragma once

#include "..\..\src\linked.hpp"

/*
    Test parentage
*/

void parentage_none()
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    auto parentage { tree::parentage(root) };
    if ( parentage != tree::Parentage::none ) throw std::runtime_error("Wrong parentage Parentage::none.");
}

void parentage_both()
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    root->left(4);
    root->right(12);
    auto parentage { tree::parentage(root) };
    if ( parentage != tree::Parentage::both ) throw std::runtime_error("Wrong parentage Parentage::both.");
}

void parentage_only_right()
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    root->right(12);
    auto parentage { tree::parentage(root) };
    if ( parentage != tree::Parentage::only_right ) throw std::runtime_error("Wrong parentage Parentage::only_right.");
}

void parentage_only_left()
{
    auto root { std::make_unique<tree::Node<int>>(7) };
    root->left(4);
    auto parentage { tree::parentage(root) };
    if ( parentage != tree::Parentage::only_left ) throw std::runtime_error("Wrong parentage Parentage::only_left.");
}
