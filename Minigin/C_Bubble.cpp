#include "MiniginPCH.h"
#include "C_Bubble.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "C_Movement.h"
#include "LevelManager.h"
#include "../BubbleBobble/Maita.h"
#include "../BubbleBobble/ZenChan.h"
#include "../BubbleBobble/Bubble.h"
#include "C_EnemyCollision.h"

dae::C_Bubble::C_Bubble(GameObject* owner)
	: Component(owner)
	, m_Timer{0.0f}
{
}

void dae::C_Bubble::Update()
{
	// check if maita hit
	for (auto maita : LevelManager::GetInstance().GetMaita())
	{
		if (m_spOwner->GetComponent<C_Movement>())
		{
			if (maita->GetComponent<C_EnemyCollision>()->HitBubble(dynamic_cast<Bubble*>(m_spOwner)))
			{
				m_spOwner->destroy();
				return;
			}
		}
	}
	// check if zenchan hit
	for (auto zenchan : LevelManager::GetInstance().GetZenChan())
	{
		if (m_spOwner->GetComponent<C_Movement>())
		{
			if (zenchan->GetComponent<C_EnemyCollision>()->HitBubble(dynamic_cast<Bubble*>(m_spOwner)))
			{
				m_spOwner->destroy();
				return;
			}
		}
	}
	m_Timer += TimeManager::GetInstance().GetDeltaTime();
	if (m_Timer >= 1.0f && m_Timer < 3.0f)
	{
		m_spOwner->GetComponent<C_Movement>()->Fall(-0.2f);
		m_spOwner->GetComponent<C_Movement>()->Move(0.0f);
		m_Timer = 3.0f;
	}
	if (m_Timer >= 5.0f)
	{
		m_spOwner->destroy();
	}
}

void dae::C_Bubble::Render() const
{
}
