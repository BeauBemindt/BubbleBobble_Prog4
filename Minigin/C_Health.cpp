#include "MiniginPCH.h"
#include "C_Health.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "C_Player.h"
#include "TimeManager.h"

dae::C_Health::C_Health(GameObject* owner)
	: Component(owner)
	, m_Health{3}
	, m_DamageInterval{}
{
}

void dae::C_Health::Update()
{
	m_DamageInterval += TimeManager::GetInstance().GetDeltaTime();
}

void dae::C_Health::Render() const
{
}

void dae::C_Health::Damage()
{
	if (m_DamageInterval >= 1.0f)
	{
		--m_Health;
		std::cout << m_Health << std::endl;
		m_DamageInterval = 0.0f;
	}
}

int dae::C_Health::GetHealth() const
{
	return m_Health;
}
