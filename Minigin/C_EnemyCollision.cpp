#include "MiniginPCH.h"
#include "C_EnemyCollision.h"
#include "GameObject.h"
#include "C_Sprite.h"
#include "C_Movement.h"
#include "TimeManager.h"
#include "C_InputHandling.h"
#include "PlayerState.h"
#include "../BubbleBobble/Bubble.h"
#include "C_BubbleBehaviour.h"
#include "C_MaitaBehaviour.h"
#include "C_ZenChanBehaviour.h"

dae::C_EnemyCollision::C_EnemyCollision(GameObject* owner)
	: Component(owner)
{
}

void dae::C_EnemyCollision::Update()
{
}

void dae::C_EnemyCollision::Render() const
{
}

bool dae::C_EnemyCollision::HandleCollision(GameObject* other)
{
	if (!m_spOwner->GetComponent<C_BubbleBehaviour>()->GetIsBubbled())
	{
		float width{ m_spOwner->GetComponent<C_Sprite>()->GetWidth() };
		float height{ m_spOwner->GetComponent<C_Sprite>()->GetHeight() };
		float posX{ m_spOwner->m_Transform.GetPosition().x };
		float posY{ m_spOwner->m_Transform.GetPosition().y };

		float otherWidth{ other->GetComponent<C_Sprite>()->GetWidth() };
		float otherHeight{ other->GetComponent<C_Sprite>()->GetHeight() };
		float otherPosX{ other->m_Transform.GetPosition().x };
		float otherPosY{ other->m_Transform.GetPosition().y };

		float dX = (posX + width / 2) - (otherPosX + otherWidth / 2);
		float dY = (posY + height / 2) - (otherPosY + otherHeight / 2);

		float thicknessX = width / 2 + otherWidth / 2;
		float thicknessY = height / 2 + otherHeight / 2;

		if (sqrt(pow(dX, 2)) <= thicknessX && sqrt(pow(dY, 2)) <= thicknessY)
		{
			if (dY < thicknessY)
			{
				if (dX < 0.0f)
				{
					if (m_spOwner->GetComponent<C_MaitaBehaviour>())
					{
						m_spOwner->GetComponent<C_Sprite>()->SetRect(float(m_spOwner->GetComponent<C_Sprite>()->GetRect().x), 48
							, float(m_spOwner->GetComponent<C_Sprite>()->GetRect().w), float(m_spOwner->GetComponent<C_Sprite>()->GetRect().h));
					}
					else
					{
						m_spOwner->GetComponent<C_Sprite>()->SetRect(float(m_spOwner->GetComponent<C_Sprite>()->GetRect().x), 16
							, float(m_spOwner->GetComponent<C_Sprite>()->GetRect().w), float(m_spOwner->GetComponent<C_Sprite>()->GetRect().h));
					}

					m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x -
						m_spOwner->GetComponent<C_Movement>()->GetSpeed() * 1.0f * TimeManager::GetInstance().GetDeltaTime(),
						m_spOwner->m_Transform.GetPosition().y);

					m_spOwner->GetComponent<C_Movement>()->Move(-0.25f);
				}
				else if (dX > 0.0f)
				{
					m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x +
						m_spOwner->GetComponent<C_Movement>()->GetSpeed() * 1.0f * TimeManager::GetInstance().GetDeltaTime(),
						m_spOwner->m_Transform.GetPosition().y);

					m_spOwner->GetComponent<C_Movement>()->Move(0.25f);
					if (m_spOwner->GetComponent<C_MaitaBehaviour>())
					{
						m_spOwner->GetComponent<C_Sprite>()->SetRect(float(m_spOwner->GetComponent<C_Sprite>()->GetRect().x), 32
							, float(m_spOwner->GetComponent<C_Sprite>()->GetRect().w), float(m_spOwner->GetComponent<C_Sprite>()->GetRect().h));
					}
					else
					{
						m_spOwner->GetComponent<C_Sprite>()->SetRect(float(m_spOwner->GetComponent<C_Sprite>()->GetRect().x), 0
							, float(m_spOwner->GetComponent<C_Sprite>()->GetRect().w), float(m_spOwner->GetComponent<C_Sprite>()->GetRect().h));
					}
				}
				if (dY < 0)
				{
					if (m_spOwner->GetComponent<C_MaitaBehaviour>())
					{
						if (m_spOwner->GetComponent<C_MaitaBehaviour>()->GetJumpingTimer() >= 0.5f
							|| m_spOwner->GetComponent<C_Movement>()->GetVelocityY() > 0.0f)
						{
							m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x, otherPosY - height - 2.0f);
							m_spOwner->GetComponent<C_Movement>()->Fall(0.0f);
							if (m_spOwner->GetComponent<C_MaitaBehaviour>())
							{
								m_spOwner->GetComponent<C_MaitaBehaviour>()->IsJumping(false);
							}
							else
							{
								m_spOwner->GetComponent<C_ZenChanBehaviour>()->IsJumping(false);
							}
						}
					}
					else
					{
						if (m_spOwner->GetComponent<C_ZenChanBehaviour>()->GetJumpingTimer() >= 0.5f
							|| m_spOwner->GetComponent<C_Movement>()->GetVelocityY() > 0.0f)
						{
							m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x, otherPosY - height - 2.0f);
							m_spOwner->GetComponent<C_Movement>()->Fall(0.0f);
							if (m_spOwner->GetComponent<C_MaitaBehaviour>())
							{
								m_spOwner->GetComponent<C_MaitaBehaviour>()->IsJumping(false);
							}
							else
							{
								m_spOwner->GetComponent<C_ZenChanBehaviour>()->IsJumping(false);
							}
						}
					}
				}
				return true;
			}
		}
	}
	return false;
}

bool dae::C_EnemyCollision::CheckCollisionToFall(GameObject* other)
{
	bool jumping{};
	if (m_spOwner->GetComponent<C_MaitaBehaviour>())
	{
		jumping = m_spOwner->GetComponent<C_MaitaBehaviour>()->GetJumping();
	}
	else
	{
		jumping = m_spOwner->GetComponent<C_ZenChanBehaviour>()->GetJumping();
	}
	if (!m_spOwner->GetComponent<C_BubbleBehaviour>()->GetIsBubbled() && !jumping)
	{
		float width{ m_spOwner->GetComponent<C_Sprite>()->GetWidth() };
		float height{ m_spOwner->GetComponent<C_Sprite>()->GetHeight() };
		float posX{ m_spOwner->m_Transform.GetPosition().x };
		float posY{ m_spOwner->m_Transform.GetPosition().y };

		float otherWidth{ other->GetComponent<C_Sprite>()->GetWidth() };
		float otherHeight{ other->GetComponent<C_Sprite>()->GetHeight() };
		float otherPosX{ other->m_Transform.GetPosition().x };
		float otherPosY{ other->m_Transform.GetPosition().y };

		float dX = (posX + width / 2) - (otherPosX + otherWidth / 2);
		float dY = (posY + height / 2) - (otherPosY + otherHeight / 2);

		float thicknessX = width / 2 + otherWidth / 2;
		float thicknessY = height / 2 + otherHeight / 2;

		if (sqrt(pow(dX, 2)) <= thicknessX && sqrt(pow(dY, 2)) <= thicknessY * 1.5f)
		{
			return true;
		}
		return false;
	}
	return true;
}

bool dae::C_EnemyCollision::HitBubble(dae::Bubble* bubble)
{
	if (!m_spOwner->GetComponent<C_BubbleBehaviour>()->GetIsBubbled())
	{
		float width{ m_spOwner->GetComponent<C_Sprite>()->GetWidth() };
		float height{ m_spOwner->GetComponent<C_Sprite>()->GetHeight() };
		float posX{ m_spOwner->m_Transform.GetPosition().x };
		float posY{ m_spOwner->m_Transform.GetPosition().y };

		float otherWidth{ bubble->GetComponent<C_Sprite>()->GetWidth() };
		float otherHeight{ bubble->GetComponent<C_Sprite>()->GetHeight() };
		float otherPosX{ bubble->m_Transform.GetPosition().x };
		float otherPosY{ bubble->m_Transform.GetPosition().y };

		float dX = (posX + width / 2) - (otherPosX + otherWidth / 2);
		float dY = (posY + height / 2) - (otherPosY + otherHeight / 2);

		float thicknessX = width / 2 + otherWidth / 2;
		float thicknessY = height / 2 + otherHeight / 2;

		if (sqrt(pow(dX, 2)) <= thicknessX && sqrt(pow(dY, 2)) <= thicknessY)
		{
			auto sprite = m_spOwner->GetComponent<C_Sprite>();
			if (m_spOwner->GetComponent<C_MaitaBehaviour>())
			{
				sprite->SetRect(float(sprite->GetRect().x), 80, float(sprite->GetRect().w), float(sprite->GetRect().h));
			}
			else
			{
				sprite->SetRect(float(sprite->GetRect().x), 64, float(sprite->GetRect().w), float(sprite->GetRect().h));
			}
			m_spOwner->GetComponent<C_BubbleBehaviour>()->IsBubbled(true);
			m_spOwner->GetComponent<C_Movement>()->Fall(-0.2f);
			m_spOwner->GetComponent<C_Movement>()->Move(0.0f);
			return true;
		}
	}
	return false;
}
