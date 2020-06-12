#include "MiniginPCH.h"
#include "PlayerState.h"
#include "Command.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "C_InputHandling.h"
#include "C_Player.h"


void dae::JumpingState::Update(GameObject* owner)
{
	m_Timer += TimeManager::GetInstance().GetDeltaTime();
	owner->GetComponent<C_Movement>()->Fall(-1.5f + m_Timer * 3.0f);
	if (m_Timer >= 1.0f)
	{
		owner->GetComponent<C_InputHandling>()->GetState()->OnExit(owner);
		owner->GetComponent<C_InputHandling>()->SetState(new FallingState());
		owner->GetComponent<C_InputHandling>()->GetState()->OnEnter(owner);
	}
}

void dae::JumpingState::OnEnter(GameObject*)
{
	m_ID = State::stateID::Jumping;
	m_Timer = 0.0f;
}

void dae::JumpingState::OnExit(GameObject*)
{
}

void dae::JumpingState::HandleInput(GameObject* owner)
{
	m_Commands = InputManager::GetInstance().HandleInput(m_ID, owner->GetComponent<C_Player>()->GetNumber());
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
	m_Commands = InputManager::GetInstance().HandleInput(m_ID, owner->GetComponent<C_Player>()->GetNumber());
	for (auto command : m_Commands)
	{
		if (command)
		{
			command->Execute(owner);
		}
	}
}

void dae::FallingState::Update(GameObject* owner)
{
	m_Timer += TimeManager::GetInstance().GetDeltaTime();
	owner->GetComponent<C_Movement>()->Fall(0.5f + m_Timer * 1.0f);
}

void dae::FallingState::OnEnter(GameObject*)
{
	m_ID = State::stateID::Falling;
	m_Timer = 0.0f;
}

void dae::FallingState::OnExit(GameObject*)
{
}

void dae::FallingState::HandleInput(GameObject* owner)
{
	m_Commands = InputManager::GetInstance().HandleInput(m_ID, owner->GetComponent<C_Player>()->GetNumber());
	for (auto command : m_Commands)
	{
		if (command)
		{
			command->Execute(owner);
		}
	}
}
