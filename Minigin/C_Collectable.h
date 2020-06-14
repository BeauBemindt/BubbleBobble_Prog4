#pragma once
#include "Component.h"

namespace dae
{
	class PlayerCharacter;
	class C_Collectable : public Component
	{
	public:
		C_Collectable(GameObject* owner);
		void Update() override;
		void Render() const override;
		void SetPoints(int points);
		bool Collision(PlayerCharacter* player) const;
		int GetPoints() const;
	private:
		bool m_Collectable;
		int m_Points;
	};
}

