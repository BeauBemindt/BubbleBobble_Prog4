#pragma once
#include <Memory>
#include "Component.h"
#include "Subject.h"

namespace dae
{
    class Observer : public Component
    {
    public:
        Observer(GameObject* owner);
        virtual void Notify(EVENT event) = 0;
        virtual void Update() override = 0;
        virtual void Render() const override = 0;
    private:
        std::shared_ptr<Subject> m_spSubject;
    };
}
