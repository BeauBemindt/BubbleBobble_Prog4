#pragma once
#include "Component.h"

namespace dae
{
	class C_Collision : public Component
	{
	public:
		C_Collision(GameObject* owner);
		void Update() override;
		void Render() const override;
		bool HandleCollision(GameObject* other);
		bool CheckCollisionToFall(GameObject* other);
	private:
	};
}

