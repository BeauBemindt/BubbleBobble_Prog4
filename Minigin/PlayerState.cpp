#include "MiniginPCH.h"
#include "PlayerState.h"
#include "Command.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "C_InputHandling.h"

void dae::JumpingState::Update(GameObject* owner)
{
	owner->GetComponent<C_Movement>()->Fall(-1.5f + TimeManager::GetInstance().GetTime() * 2.5f);
	if (TimeManager::GetInstance().GetTime() >= 1.0f)
	{
		owner->GetComponent<C_InputHandling>()->GetState()->OnExit(owner);
		owner->GetComponent<C_InputHandling>()->SetState(new FallingState());
		owner->GetComponent<C_InputHandling>()->GetState()->OnEnter(owner);
	}
}

void dae::JumpingState::OnEnter(GameObject* owner)
{
	m_ID = State::stateID::Jumping;
	owner->GetComponent<C_Movement>()->Fall(-1.5);
	TimeManager::GetInstance().StartTiming();
}

void dae::JumpingState::OnExit(GameObject*)
{
	TimeManager::GetInstance().StopTimimg();
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

void dae::RunningState::Update(GameObject*)
{
}

void dae::RunningState::OnEnter(GameObject* owner)
{
	m_ID = State::stateID::Running;
	owner->GetComponent<C_Movement>()->Fall(0.0f);
}

void dae::RunningState::OnExit(GameObject*)
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

void dae::FallingState::Update(GameObject*)
{
}

void dae::FallingState::OnEnter(GameObject* owner)
{
	m_ID = State::stateID::Falling;
	owner->GetComponent<C_Movement>()->Fall(1.0f);
}

void dae::FallingState::OnExit(GameObject*)
{
}

void dae::FallingState::HandleInput(GameObject* owner)
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
