#pragma once
#include "Component.h"

namespace dae
{
	class Bubble;
	class C_EnemyCollision : public Component
	{
	public:
		C_EnemyCollision(GameObject* owner);
		void Update() override;
		void Render() const override;
		bool HandleCollision(GameObject* other);
		bool CheckCollisionToFall(GameObject* other);
		bool HitBubble(Bubble* bubble);
	private:
	};
}

