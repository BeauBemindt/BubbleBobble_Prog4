#pragma once
#include "Component.h"

namespace dae
{
	class C_Movement : public Component
	{
	public:
		C_Movement(GameObject* owner);
		void Update() override;
		void Render() const override;
		void Move(float multiplier);
		void Fall(float multiplier);
		float GetGravity() const;
		float GetSpeed() const;

	private:
		float m_VelocityX;
		float m_VelocityY;
		float m_Gravity;
		float m_Speed;
		bool m_Jumping;
	};
}
