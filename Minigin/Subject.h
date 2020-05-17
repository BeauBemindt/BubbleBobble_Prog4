#pragma once
#include "Component.h"
#include <list>

namespace dae
{
    class Observer;
    class Subject
    {
    public:

        Subject();

        void attach(Observer* observer);
        void detach(Observer* observer);

        virtual void notify() = 0;

    private:

        std::list<std::shared_ptr<Observer>> m_Observers;
    };
}

