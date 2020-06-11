#include "MiniginPCH.h"
#include "C_Movement.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "C_InputHandling.h"
#include "PlayerState.h"

dae::C_Movement::C_Movement(GameObject* owner)
	: Component(owner)
	, m_VelocityX{0.0f}
	, m_Gravity{300.0f}
	, m_Speed{100.0f}
	, m_Jumping{false}
	, m_JumpTimer{1.0f}
	, m_VelocityY{}
{
	m_VelocityY = m_Gravity;
}

void dae::C_Movement::Update()
{
	if (m_Jumping)
	{
		m_JumpTimer -= TimeManager::GetInstance().GetDeltaTime();
		if (m_JumpTimer < 0.0f)
		{
			m_JumpTimer = 0.0f;
		}
		m_VelocityY = m_Gravity - m_JumpTimer * m_Gravity * 2;
	}
	if (m_spOwner->m_Transform.GetPosition().y <= 300.0f || m_Jumping)
	{
		m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x,
			m_spOwner->m_Transform.GetPosition().y + m_VelocityY * TimeManager::GetInstance().GetDeltaTime());
	}
	m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x + m_VelocityX * TimeManager::GetInstance().GetDeltaTime(),
		m_spOwner->m_Transform.GetPosition().y);
}

void dae::C_Movement::Render() const
{
}

void dae::C_Movement::Move(float multiplier)
{
	m_VelocityX = m_Speed * multiplier;
}

void dae::C_Movement::Jump()
{
	m_Jumping = true;
}

void dae::C_Movement::EndJumping()
{
	if (m_JumpTimer < 0.8)
	{
		m_JumpTimer = 1.0f;
		m_VelocityY = m_Gravity;
		m_Jumping = false;
		*m_spOwner->GetComponent<C_InputHandling>()->GetState() = PlayerState::m_RunningState;
		PlayerState::m_RunningState.OnEnter();
	}
}

void dae::C_Movement::Fall()
{
	m_VelocityY = m_Gravity;
	m_Jumping = false;
	//*m_spOwner->GetComponent<C_InputHandling>()->GetState() = PlayerState::m_RunningState;
	//PlayerState::m_RunningState.OnEnter();
}

float dae::C_Movement::GetGravity() const
{
	return m_Gravity;
}

float dae::C_Movement::GetSpeed() const
{
	return m_Speed;
}
