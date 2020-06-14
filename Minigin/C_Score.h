#pragma once
#include "Component.h"

namespace dae
{
	class C_Score : public Component
	{
	public:
		C_Score(GameObject* owner);
		void Update() override;
		void Render() const override;
		void Add(int amount);
		int GetScore() const;
	private:
		int m_Score;
	};
}

