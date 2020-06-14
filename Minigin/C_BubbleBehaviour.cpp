#include "MiniginPCH.h"
#include "C_BubbleBehaviour.h"
#include "C_Sprite.h"
#include "C_Movement.h"
#include "TimeManager.h"
#include "LevelManager.h"
#include "C_Fire.h"
#include "C_Movement.h"
#include "GameObject.h"

dae::C_BubbleBehaviour::C_BubbleBehaviour(GameObject* owner)
	: Component(owner)
	, m_Bubbled{}
	, m_BubbleTimer{}
{
}

void dae::C_BubbleBehaviour::Update()
{
	if (m_Bubbled)
	{
		m_BubbleTimer += TimeManager::GetInstance().GetDeltaTime();
		if (m_BubbleTimer >= 2.0f) // pop out if player not hit
		{
			IsBubbled(false);
			m_BubbleTimer = 0.0f;
			auto sprite = m_spOwner->GetComponent<C_Sprite>();
			sprite->SetRect(float(sprite->GetRect().x), 32, float(sprite->GetRect().w), float(sprite->GetRect().h));
			m_spOwner->GetComponent<C_Movement>()->Fall(1.0f);
		}
	}
}

void dae::C_BubbleBehaviour::Render() const
{
}

void dae::C_BubbleBehaviour::IsBubbled(bool bubbled)
{
	m_Bubbled = bubbled;
	if (bubbled)
	{
		m_spOwner->GetComponent<C_Movement>()->Move(0.0f);
	}
}

bool dae::C_BubbleBehaviour::GetIsBubbled() const
{
	return m_Bubbled;
}
