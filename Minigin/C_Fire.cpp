#include "MiniginPCH.h"
#include "C_Fire.h"
#include "TimeManager.h"
#include "../BubbleBobble/Bubble.h"
#include "SceneManager.h"
#include "Scene.h"
#include "C_Sprite.h"
#include "C_Player.h"

dae::C_Fire::C_Fire(GameObject* owner)
	: Component(owner)
	, m_Timer{}
	, m_Timing{false}
{
}

void dae::C_Fire::Update()
{
	if (m_Timing)
	{
		m_Timer -= TimeManager::GetInstance().GetDeltaTime();

		if (m_Timer <= 0.0f)
		{
			m_Timing = false;
			m_Timer = 0.0f;
			auto sprite = m_spOwner->GetComponent<C_Sprite>();
			sprite->SetRect(float(sprite->GetRect().x), float(sprite->GetRect().y - 32), float(sprite->GetRect().w), float(sprite->GetRect().h));
		}
	}
}

void dae::C_Fire::Render() const
{
}

void dae::C_Fire::Fire(float dir)
{
	if (m_Timer == 0.0f)
	{
		if (dir <= 0.0f)
		{
			auto go = std::make_shared<Bubble>(m_spOwner->m_Transform.GetPosition().x - m_spOwner->GetComponent<C_Sprite>()->GetWidth()
				, m_spOwner->m_Transform.GetPosition().y, m_spOwner, -2.0f);
			SceneManager::GetInstance().GetCurrentScene().Add(go);
		}
		else
		{
			auto go = std::make_shared<Bubble>(m_spOwner->m_Transform.GetPosition().x + m_spOwner->GetComponent<C_Sprite>()->GetWidth()
				, m_spOwner->m_Transform.GetPosition().y, m_spOwner, 2.0f);
			SceneManager::GetInstance().GetCurrentScene().Add(go);
		}
		m_Timer = 0.5f;
		m_Timing = true;
	}
}
