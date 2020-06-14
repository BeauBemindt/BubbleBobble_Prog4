#include "MiniginPCH.h"
#include "C_Collectable.h"
#include "GameObject.h"
#include "C_Movement.h"
#include "LevelManager.h"
#include "../BubbleBobble/PlayerCharacter.h"
#include "../BubbleBobble/Collectable.h"
#include "C_Collision.h"

dae::C_Collectable::C_Collectable(GameObject* owner)
	: Component(owner)
	, m_Collectable{}
	, m_Points{}
{
}

void dae::C_Collectable::Update()
{
	if (m_spOwner->m_Transform.GetPosition().y >= 580.0f - 64.0f) // become collectable when dropping in floor
	{
		m_Collectable = true;
		m_spOwner->GetComponent<C_Movement>()->Fall(0.0f);
	}
}

void dae::C_Collectable::Render() const
{
}

void dae::C_Collectable::SetPoints(int points)
{
	m_Points = points;
}

bool dae::C_Collectable::Collision(dae::PlayerCharacter* player) const
{
	if (m_Collectable)
	{
		if (player->GetComponent<C_Collision>()->HitCollectable(dynamic_cast<Collectable*>(m_spOwner))) // get picked up
		{
			m_spOwner->destroy();
			return true;
		}
		return false;
	}
	return false;
}

int dae::C_Collectable::GetPoints() const
{
	return m_Points;
}
