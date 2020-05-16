#pragma once
#include "Component.h"
#include <Memory>

namespace dae
{
    enum class EVENT
    {
        a,
        b,
        c
    };
    class C_Subject;
    class C_Observer : public dae::Component
    {
    public:

        C_Observer(GameObject* owner);

        void Update() override;
        void Render() const override;

        void Notify(EVENT event);

    private:

        bool m_Notified;
        EVENT m_Event;
    };
}
