#pragma once
#include "ObserverInterface.hpp"

class Subject
{
    virtual ~Subject() = 0;
    virtual void attachObserver(ObserverInterface observer) = 0;
    virtual void detachObserver(ObserverInterface observer) = 0;
    virtual void notifyObservers() = 0;
};
