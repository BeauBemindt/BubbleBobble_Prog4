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
	, m_VelocityY{m_Gravity}
{
	m_VelocityY = m_Gravity;
}

void dae::C_Movement::Update()
{
	// update position according to velocity
	m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x + m_VelocityX * TimeManager::GetInstance().GetDeltaTime(),
		m_spOwner->m_Transform.GetPosition().y + m_VelocityY * TimeManager::GetInstance().GetDeltaTime());

	// reappear when going through top or bottom side of map
	if (m_spOwner->m_Transform.GetPosition().y >= 580.0f)
	{
		m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x, 101.0f);
	}
	else if (m_spOwner->m_Transform.GetPosition().y <= 100.0f)
	{
		m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x, 579.0f);
	}
}

void dae::C_Movement::Render() const
{
}

void dae::C_Movement::Move(float multiplier)
{
	m_VelocityX = m_Speed * multiplier;
}

void dae::C_Movement::Fall(float multiplier)
{
	m_VelocityY = m_Gravity * multiplier;
}

float dae::C_Movement::GetGravity() const
{
	return m_Gravity;
}

float dae::C_Movement::GetSpeed() const
{
	return m_Speed;
}

float dae::C_Movement::GetVelocityY() const
{
	return m_VelocityY;
}
