#pragma once 
#include "../Minigin/Component.h"

namespace dae
{
	class C_Fire : public Component
	{
	public:
		C_Fire(GameObject* owner);
		void Update() override;
		void Render() const override;
		void Fire(float dir);
	private:
		float m_Timer;
	};

}
