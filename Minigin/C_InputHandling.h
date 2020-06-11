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
		std::shared_ptr<PlayerState> GetState();
		void SetState(PlayerState* state);
	
	private:
		std::vector<Command*> m_Commands;
		std::shared_ptr<PlayerState> m_spState;
	};
}

