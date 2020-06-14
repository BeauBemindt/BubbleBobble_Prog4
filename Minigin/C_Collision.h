#pragma once
#include "Component.h"

namespace dae
{
	class Collectable;
	class Boulder;
	class C_Collision : public Component
	{
	public:
		C_Collision(GameObject* owner);
		void Update() override;
		void Render() const override;
		bool HandleCollision(GameObject* other);
		bool CheckCollisionToFall(GameObject* other);
		bool HitBoulder(Boulder* bubble);
		bool HitCollectable(Collectable* collectable);
	private:
	};
}

