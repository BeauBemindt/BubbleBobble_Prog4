#pragma once
#include "Component.h"

namespace dae
{
	class C_Bubble : public Component
	{
	public:
		C_Bubble(GameObject* owner);
		void Update() override;
		void Render() const override;
	private:
		float m_Timer;
	};
}
