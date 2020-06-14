#include "MiniginPCH.h"
#include "C_ZenChanBehaviour.h"
#include "C_Sprite.h"
#include "C_Movement.h"
#include "TimeManager.h"
#include "LevelManager.h"
#include "C_Fire.h"
#include "C_BubbleBehaviour.h"
#include "C_Health.h"

dae::C_ZenChanBehaviour::C_ZenChanBehaviour(GameObject* owner)
	: Component(owner)
	, m_pTarget{}
	, m_Charging{}
	, m_ChargingTimer{}
	, m_WanderingTimer{ 5.0f }
	, m_JumpingTimer{ 0.0f }
	, m_TimerToJump{ 5.0f }
	, m_Jumping{}
{
}

void dae::C_ZenChanBehaviour::Update()
{
	// looks for target
	PlayerInArea();

	// if not in bubble
	if (!m_spOwner->GetComponent<C_BubbleBehaviour>()->GetIsBubbled())
	{
		// if target found
		if (m_pTarget)
		{
			// chech if target is close enoug to attack
			float width{ m_spOwner->GetComponent<C_Sprite>()->GetWidth() };
			float height{ m_spOwner->GetComponent<C_Sprite>()->GetHeight() };
			float posX{ m_spOwner->m_Transform.GetPosition().x };
			float posY{ m_spOwner->m_Transform.GetPosition().y };
			float otherWidth = m_pTarget->GetComponent<C_Sprite>()->GetWidth();
			float otherHeight = m_pTarget->GetComponent<C_Sprite>()->GetHeight();
			float otherPosX = m_pTarget->m_Transform.GetPosition().x;
			float otherPosY = m_pTarget->m_Transform.GetPosition().y;

			float dX = (posX + width / 2) - (otherPosX + otherWidth / 2);
			float dY = (posY + height / 2) - (otherPosY + otherHeight / 2);

			float thicknessX = width / 2 + otherWidth / 2 + 100.0f;
			float thicknessY = height / 2 + otherHeight / 2 + 16.0f;

			if (sqrt(pow(dX, 2)) <= thicknessX && sqrt(pow(dY, 2)) <= thicknessY && dY > -10.0f)
			{
				m_spOwner->GetComponent<C_Sprite>()->Pause();
				m_spOwner->GetComponent<C_Movement>()->Move(0.0f);
				m_Charging = true;
			}
		}
		// charge to attack
		if (m_Charging)
		{
			m_ChargingTimer += TimeManager::GetInstance().GetDeltaTime();
			if (m_ChargingTimer >= 2.0f)
			{
				if (m_spOwner->GetComponent<C_Sprite>()->GetRect().y % 32 == 0.0f)
				{
					m_spOwner->GetComponent<C_Movement>()->Move(3.0f);
				}
				else
				{
					m_spOwner->GetComponent<C_Movement>()->Move(-3.0f);
				}
				if (m_ChargingTimer >= 3.0f)
				{
					m_spOwner->GetComponent<C_Movement>()->Move(0.0f);
					m_Charging = false;
					m_ChargingTimer = 0.0f;
				}
			}
		}
		else // jump on random interval or wanders around
		{
			m_TimerToJump -= TimeManager::GetInstance().GetDeltaTime();
			m_WanderingTimer += TimeManager::GetInstance().GetDeltaTime();
			if (m_WanderingTimer >= 5.0f)
			{
				int random{ rand() % 2 - 1 };
				auto sprite = m_spOwner->GetComponent<C_Sprite>();
				if (random >= 0)
				{
					m_spOwner->GetComponent<C_Movement>()->Move(0.25f);
					sprite->SetRect(float(sprite->GetRect().x), 0, float(sprite->GetRect().w), float(sprite->GetRect().h));
				}
				else
				{
					m_spOwner->GetComponent<C_Movement>()->Move(-0.25f);
					sprite->SetRect(float(sprite->GetRect().x), 16, float(sprite->GetRect().w), float(sprite->GetRect().h));
				}
				m_WanderingTimer = 0.0f;
			}
			if (m_TimerToJump <= 0.0f)
			{
				m_TimerToJump = float(rand() % 8 + 3.0f);
				m_Jumping = true;
			}
			if (m_Jumping)
			{
				m_JumpingTimer += TimeManager::GetInstance().GetDeltaTime();
				m_spOwner->GetComponent<C_Movement>()->Fall(-1.5f + m_JumpingTimer * 3.0f);
				if (m_JumpingTimer >= 1.0f)
				{
					m_Jumping = false;
					m_JumpingTimer = 0.0f;
				}
			}
		}
	}
}

void dae::C_ZenChanBehaviour::Render() const
{
}

void dae::C_ZenChanBehaviour::IsJumping(bool jumping)
{
	m_Jumping = jumping;
	if (!jumping)
	{
		m_JumpingTimer = 0.0f;
	}
}

bool dae::C_ZenChanBehaviour::GetJumping() const
{
	return m_Jumping;
}

float dae::C_ZenChanBehaviour::GetJumpingTimer() const
{
	return m_JumpingTimer;
}

void dae::C_ZenChanBehaviour::RemoveTarget()
{
	m_pTarget = nullptr;
}

void dae::C_ZenChanBehaviour::PlayerInArea()
{
	// if not in bubble
	if (!m_spOwner->GetComponent<C_BubbleBehaviour>()->GetIsBubbled() && !m_Charging)
	{
		// check if player in area
		PlayerCharacter* target{};
		float width{ m_spOwner->GetComponent<C_Sprite>()->GetWidth() };
		float height{ m_spOwner->GetComponent<C_Sprite>()->GetHeight() };
		float posX{ m_spOwner->m_Transform.GetPosition().x };
		float posY{ m_spOwner->m_Transform.GetPosition().y };
		float otherWidth{};
		float otherHeight{};
		float otherPosX{};
		float otherPosY{};

		float dX = (posX + width / 2) - (otherPosX + otherWidth / 2);
		float dY = (posY + height / 2) - (otherPosY + otherHeight / 2);

		float thicknessX{};
		float thicknessY{};

		for (auto player : LevelManager::GetInstance().GetPlayers())
		{
			otherWidth = player->GetComponent<C_Sprite>()->GetWidth();
			otherHeight = player->GetComponent<C_Sprite>()->GetHeight();
			otherPosX = player->m_Transform.GetPosition().x;
			otherPosY = player->m_Transform.GetPosition().y;

			dX = (posX + width / 2) - (otherPosX + otherWidth / 2);
			dY = (posY + height / 2) - (otherPosY + otherHeight / 2);

			thicknessX = width / 2 + otherWidth / 2 + 150.0f;
			thicknessY = height / 2 + otherHeight / 2 + 50.0f;

			if (sqrt(pow(dX, 2)) <= thicknessX && sqrt(pow(dY, 2)) <= thicknessY && dY > -10.0f)
			{
				target = player.get();
				break;
			}
		}
		m_pTarget = target;
		// target found
		if (m_pTarget)
		{
			auto sprite = m_spOwner->GetComponent<C_Sprite>();
			if (!m_Charging)
			{
				if (dX < 0)
				{
					m_spOwner->GetComponent<C_Movement>()->Move(0.5f);
					sprite->SetRect(float(sprite->GetRect().x), 0.0f, 16.0f, 16.0f);
				}
				else
				{
					m_spOwner->GetComponent<C_Movement>()->Move(-0.5f);
					sprite->SetRect(float(sprite->GetRect().x), 16.0f, 16.0f, 16.0f);
				}
			}
			else if (dX < 0)
			{
				sprite->SetRect(float(sprite->GetRect().x), 0.0f, 16.0f, 16.0f);
			}
			else
			{
				sprite->SetRect(float(sprite->GetRect().x), 16.0f, 16.0f, 16.0f);
			}
		}
	}
}
