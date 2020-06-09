#pragma once
#include "Component.h"
#include "Command.h"

namespace dae
{
	class C_InputHandling : public Component
	{
	public:
		C_InputHandling(GameObject* owner);
		void Update() override;
		void Render() const override;
		void HandleInput();
	
	private:
		std::vector<Command*> m_Commands;
	};
}

