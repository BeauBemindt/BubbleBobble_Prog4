#pragma once
#include "Component.h"
#include <Memory>

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
    class Subject;
    class Observer
    {
    public:
        void Attach(Subject* subject);
        void detach();
        virtual void Notify(EVENT event) = 0;
    private:
        Subject* m_pSubject;
    };
}
