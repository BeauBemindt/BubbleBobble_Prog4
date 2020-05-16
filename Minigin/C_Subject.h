#pragma once
#include "Component.h"
#include <list>

namespace dae
{
    class C_Observer;
    class C_Subject : public dae::Component
    {
    public:

        C_Subject(GameObject* owner);

        void Update() override;
        void Render() const override;

        void attach(C_Observer* observer);
        void detach(C_Observer* observer);

        void notify();

    private:

        std::list<std::shared_ptr<C_Observer>> m_Observers;
    };
}

