#pragma once
#include <list>
#include "Component.h"

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

    class C_Observer;
    class C_Subject : Component
    {
    public:

        C_Subject(GameObject* owner);

        void attach(std::shared_ptr<C_Observer> observer);
        void detach(std::shared_ptr<C_Observer> observer);
        void Update() override;
        void Render() const override;

        void notify(EVENT event);

    private:

        std::list<std::shared_ptr<C_Observer>> m_Observers;
    };
}

