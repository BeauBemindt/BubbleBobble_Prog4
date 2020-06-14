#pragma once
#include "Component.h"

namespace dae
{
	class C_BubbleBehaviour : public Component
	{
	public:
		C_BubbleBehaviour(GameObject* owner);
		void Update() override;
		void Render() const override;
		void IsBubbled(bool bubbled);
		bool GetIsBubbled() const;
	private:
		bool m_Bubbled;
		float m_BubbleTimer;
	};
}
