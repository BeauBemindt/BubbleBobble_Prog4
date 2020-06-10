#include "MiniginPCH.h"
#include "PlayerState.h"
#include "Command.h"
#include "InputManager.h"

void dae::JumpingState::Update()
{
}

void dae::JumpingState::OnEnter()
{
	m_ID = State::stateID::Jumping;
}

void dae::JumpingState::OnExit()
{
}

void dae::JumpingState::HandleInput(GameObject* owner)
{
	m_Commands = InputManager::GetInstance().HandleInput(m_ID);
	for (auto command : m_Commands)
	{
		if (command)
		{
			command->Execute(owner);
		}
	}
}

void dae::RunningState::Update()
{
}

void dae::RunningState::OnEnter()
{
	m_ID = State::stateID::Running;
}

void dae::RunningState::OnExit()
{
}

void dae::RunningState::HandleInput(GameObject* owner)
{
	m_Commands = InputManager::GetInstance().HandleInput(m_ID);
	for (auto command : m_Commands)
	{
		if (command)
		{
			command->Execute(owner);
		}
	}
}
