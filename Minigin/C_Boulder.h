#pragma once
#include "Component.h"

namespace dae
{
	class C_Boulder : public Component
	{
	public:
		C_Boulder(GameObject* owner);
		void Update() override;
		void Render() const override;
	private:
		float m_Timer;
	};
}
