#pragma once
#include <Memory>
#include "Component.h"
#include "C_Subject.h"

namespace dae
{
    class C_Observer : public Component
    {
    public:
        C_Observer(GameObject* owner);
        virtual void Notify(EVENT event) = 0;
        virtual void Update() override = 0;
        virtual void Render() const override = 0;
        virtual void Attach(C_Subject* subject);
    private:
        C_Subject* m_spSubject;
    };
}
