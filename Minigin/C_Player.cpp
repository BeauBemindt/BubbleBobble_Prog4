#include "MiniginPCH.h"
#include "C_Player.h"
#include "C_Sprite.h"
#include "GameObject.h"

dae::C_Player::C_Player(GameObject* owner)
	: Component(owner)
	, m_PlayerNbr{}
{
}

void dae::C_Player::Update()
{
}

void dae::C_Player::Render() const
{
}

const int dae::C_Player::GetNumber() const
{
	return m_PlayerNbr;
}

void dae::C_Player::SetPlayer(int number)
{
	// holds what number this player is
	m_PlayerNbr = number;
	if (number == 2)
	{
		m_spOwner->GetComponent<C_Sprite>()->SetRect(0.0f, 64.0f, 16.0f, 16.0f);
	}
}
