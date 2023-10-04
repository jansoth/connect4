#pragma once
#include "Column.hpp"

/// @brief Interface for View Element of MVC Pattern
class ViewInterface
{
public:
    virtual ~ViewInterface(){};
    virtual void initialize() = 0;
};