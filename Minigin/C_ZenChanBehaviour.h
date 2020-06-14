#pragma once
#include "Component.h"
#include "../BubbleBobble/PlayerCharacter.h"

namespace dae
{
	class C_ZenChanBehaviour : public Component
	{
	public:
		C_ZenChanBehaviour(GameObject* owner);
		void Update() override;
		void Render() const override;
		void IsJumping(bool jumping);
		bool GetJumping() const;
		float GetJumpingTimer() const;
		void RemoveTarget();
	private:
		void PlayerInArea();

		PlayerCharacter* m_pTarget;
		bool m_Charging;
		float m_ChargingTimer;
		float m_WanderingTimer;
		float m_JumpingTimer;
		float m_TimerToJump;
		bool m_Jumping;
	};
}
