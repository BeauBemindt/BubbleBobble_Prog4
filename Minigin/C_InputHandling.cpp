#include "MiniginPCH.h"
#include "C_InputHandling.h"
#include "InputManager.h"

dae::C_InputHandling::C_InputHandling(GameObject* owner)
	: Component(owner)
	, m_Commands{}
{
}

void dae::C_InputHandling::Update()
{
	HandleInput();
}

void dae::C_InputHandling::Render() const
{
}

void dae::C_InputHandling::HandleInput()
{
	m_Commands = InputManager::GetInstance().HandleInput();
	for (auto command : m_Commands)
	{
		if (command)
		{
			command->Execute(m_spOwner);
		}
	}
}
