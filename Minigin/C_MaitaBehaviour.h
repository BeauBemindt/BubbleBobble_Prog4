#pragma once
#include "Component.h"
#include "../BubbleBobble/PlayerCharacter.h"

namespace dae
{
	class C_MaitaBehaviour : public Component
	{
	public:
		C_MaitaBehaviour(GameObject* owner);
		void Update() override;
		void Render() const override;
		void IsJumping(bool jumping);
		bool GetJumping() const;
		float GetJumpingTimer() const;
	private:
		void PlayerInArea();

		PlayerCharacter* m_pTarget;
		bool m_Firing;
		float m_WanderingTimer;
		float m_JumpingTimer;
		float m_TimerToJump;
		bool m_Jumping;
	};
}
