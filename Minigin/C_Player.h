#pragma once
#include "Component.h"

namespace dae
{
	class C_Player : public Component
	{
	public:
		C_Player(GameObject* owner);
		void Update() override;
		void Render() const override;
		const int GetNumber() const;
		void SetPlayer(int number);
	private:
		int m_PlayerNbr;
	};
}

