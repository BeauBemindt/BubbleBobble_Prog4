#include "MiniginPCH.h"
#include "C_Boulder.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "C_Movement.h"
#include "LevelManager.h"
#include "../BubbleBobble/PlayerCharacter.h"
#include "../BubbleBobble/Boulder.h"
#include "C_Collision.h"

dae::C_Boulder::C_Boulder(GameObject* owner)
	: Component(owner)
	, m_Timer{ 0.0f }
{
}

void dae::C_Boulder::Update()
{
	m_Timer += TimeManager::GetInstance().GetDeltaTime();
	if (m_Timer >= 1.0f)
	{
		m_spOwner->destroy();
	}
	else
	{
		for (auto player : LevelManager::GetInstance().GetPlayers())
		{
			if (player->GetComponent<C_Collision>()->HitBoulder(dynamic_cast<Boulder*>(m_spOwner)))
			{
				m_spOwner->destroy();
				break;
			}
		}
	}
}

void dae::C_Boulder::Render() const
{
}
