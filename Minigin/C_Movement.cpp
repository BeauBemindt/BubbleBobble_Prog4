#include "MiniginPCH.h"
#include "C_Movement.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "InputManager.h"

dae::C_Movement::C_Movement(GameObject* owner)
	: Component(owner)
	, m_Velocity{100.0f}
	, m_Gravity{100.0f}
	, m_Jumping{false}
	, m_JumpTimer{1.0f}
{
}

void dae::C_Movement::Update()
{
	if (m_Jumping)
	{
		m_JumpTimer -= TimeManager::GetInstance().GetDeltaTime();
		m_Gravity = 100.0f - m_JumpTimer * 200;
		if (m_JumpTimer <= 0.0f)
		{
			m_Jumping = false;
			m_Gravity = 100.0f;
			m_JumpTimer = 1.0f;
		}
	}
	if (m_spOwner->m_Transform.GetPosition().y <= 300.0f || m_Jumping)
	{
		m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x,
			m_spOwner->m_Transform.GetPosition().y + m_Gravity * TimeManager::GetInstance().GetDeltaTime());
	}
}

void dae::C_Movement::Render() const
{
}

void dae::C_Movement::Move(float multiplier)
{
	m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x + m_Velocity * multiplier * TimeManager::GetInstance().GetDeltaTime(),
		m_spOwner->m_Transform.GetPosition().y);
}

void dae::C_Movement::Jump()
{
	m_Jumping = true;
}