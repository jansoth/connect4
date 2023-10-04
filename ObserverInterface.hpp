#pragma once

/// @brief Observer Interface for Observer Pattern
class ObserverInterface
{
public:
    virtual ~ObserverInterface(){};
    virtual void drawGrid() = 0;
};