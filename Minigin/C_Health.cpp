#include "MiniginPCH.h"
#include "C_Health.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "C_Player.h"
#include "TimeManager.h"
#include "C_Subject.h"

dae::C_Health::C_Health(GameObject* owner)
	: Component(owner)
	, m_Health{4}
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
	// keeps from taking constant damage
	if (m_DamageInterval >= 0.5f)
	{
		--m_Health;
		m_DamageInterval = 0.0f;
		
		// norify healthbar
		m_spOwner->GetComponent<C_Subject>()->notify(EVENT::damaged);
	}
}

int dae::C_Health::GetHealth() const
{
	return m_Health;
}
