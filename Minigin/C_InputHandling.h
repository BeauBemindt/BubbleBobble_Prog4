#pragma once
#include "Component.h"

namespace dae
{
	class Command;
	class PlayerState;
	class C_InputHandling : public Component
	{
	public:
		C_InputHandling(GameObject* owner);
		void Update() override;
		void Render() const override;
		PlayerState* GetState();
	
	private:
		std::vector<Command*> m_Commands;
		PlayerState* m_pState;
	};
}

