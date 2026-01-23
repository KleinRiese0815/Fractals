#pragma once
#include<iostream>
struct VboIndex
{
    std::size_t value;

    explicit operator std::size_t() const { return value; }
};