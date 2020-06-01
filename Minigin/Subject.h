#pragma once
#include <list>

namespace dae
{
    enum class EVENT
    {
        // Player Events
        a,
        b,
        c,

        // Enemy Events
        d,
        e,
        f
    };

    class Observer;
    class Subject
    {
    public:

        Subject();

        void attach(std::shared_ptr<Observer> observer);
        void detach(std::shared_ptr<Observer> observer);
        ~Subject();

        void notify(EVENT event);

    private:

        std::list<std::shared_ptr<Observer>> m_Observers;
    };
}

