#pragma once
#include "Component.h"

namespace dae
{
	class C_Health : public Component
	{
	public:
		C_Health(GameObject* owner);
		void Update() override;
		void Render() const override;
		void Damage();
		int GetHealth() const;
	private:
		int m_Health;
		float m_DamageInterval;
	};
}

