#include "MiniginPCH.h"
#include "C_Collision.h"
#include "GameObject.h"
#include "C_Sprite.h"
#include "C_Movement.h"
#include "TimeManager.h"
#include "C_InputHandling.h"
#include "PlayerState.h"
#include "../BubbleBobble/Maita.h"
#include "../BubbleBobble/ZenChan.h"
#include "C_BubbleBehaviour.h"
#include "../BubbleBobble/Boulder.h"
#include "C_Health.h"

dae::C_Collision::C_Collision(GameObject* owner)
	: Component(owner)
{
}

void dae::C_Collision::Update()
{
}

void dae::C_Collision::Render() const
{
}

bool dae::C_Collision::HandleCollision(GameObject* other)
{
	float width{m_spOwner->GetComponent<C_Sprite>()->GetWidth()};
	float height{ m_spOwner->GetComponent<C_Sprite>()->GetHeight()};
	float posX{m_spOwner->m_Transform.GetPosition().x};
	float posY{ m_spOwner->m_Transform.GetPosition().y};

	float otherWidth{ other->GetComponent<C_Sprite>()->GetWidth() };
	float otherHeight{ other->GetComponent<C_Sprite>()->GetHeight() };
	float otherPosX{ other->m_Transform.GetPosition().x };
	float otherPosY{ other->m_Transform.GetPosition().y };

	float dX = (posX + width/2) - (otherPosX + otherWidth/2);
	float dY = (posY + height/2) - (otherPosY + otherHeight/2);

	float thicknessX = width / 2 + otherWidth / 2;
	float thicknessY = height / 2 + otherHeight / 2;

	if (sqrt(pow(dX, 2)) <= thicknessX && sqrt(pow(dY, 2)) <= thicknessY)
	{
		if (dynamic_cast<Maita*>(other))
		{
			if (other->GetComponent<C_BubbleBehaviour>()->GetIsBubbled())
			{
				other->destroy();
				return true;
			}
		}
		else if (dynamic_cast<ZenChan*>(other))
		{
			if (other->GetComponent<C_BubbleBehaviour>()->GetIsBubbled())
			{
				other->destroy();
				return true;
			}
			else
			{
				m_spOwner->GetComponent<C_Health>()->Damage();
			}
		}
		else if(dY < thicknessY)
		{
				if (dX < 0.0f)
				{
					m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x -
						m_spOwner->GetComponent<C_Movement>()->GetSpeed() * 1.0f * TimeManager::GetInstance().GetDeltaTime(),
						m_spOwner->m_Transform.GetPosition().y);
				}
				else if (dX > 0.0f)
				{
					m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x +
						m_spOwner->GetComponent<C_Movement>()->GetSpeed() * 1.0f * TimeManager::GetInstance().GetDeltaTime(),
						m_spOwner->m_Transform.GetPosition().y);

				}
				if (dY < 0)
				{
					if (m_spOwner->GetComponent<C_InputHandling>()->GetState().get()->m_ID == State::stateID::Falling ||
						(m_spOwner->GetComponent<C_InputHandling>()->GetState()->m_ID == State::stateID::Jumping &&
							std::static_pointer_cast<JumpingState>(m_spOwner->GetComponent<C_InputHandling>()->GetState())->m_Timer >= 0.5f))
					{
						m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x, otherPosY - height - 2.0f);
						m_spOwner->GetComponent<C_InputHandling>()->GetState()->OnExit(m_spOwner);
						m_spOwner->GetComponent<C_InputHandling>()->SetState(new RunningState());
						m_spOwner->GetComponent<C_InputHandling>()->GetState()->OnEnter(m_spOwner);
					}
				}
			return true;
		}
	}
	return false;
}

bool dae::C_Collision::CheckCollisionToFall(GameObject* other)
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
	else
	{
		return false;
	}
}

bool dae::C_Collision::HitBoulder(dae::Boulder* boulder)
{
	float width{ m_spOwner->GetComponent<C_Sprite>()->GetWidth() };
	float height{ m_spOwner->GetComponent<C_Sprite>()->GetHeight() };
	float posX{ m_spOwner->m_Transform.GetPosition().x };
	float posY{ m_spOwner->m_Transform.GetPosition().y };

	float otherWidth{ boulder->GetComponent<C_Sprite>()->GetWidth() };
	float otherHeight{ boulder->GetComponent<C_Sprite>()->GetHeight() };
	float otherPosX{ boulder->m_Transform.GetPosition().x };
	float otherPosY{ boulder->m_Transform.GetPosition().y };

	float dX = (posX + width / 2) - (otherPosX + otherWidth / 2);
	float dY = (posY + height / 2) - (otherPosY + otherHeight / 2);

	float thicknessX = width / 2 + otherWidth / 2;
	float thicknessY = height / 2 + otherHeight / 2;

	if (sqrt(pow(dX, 2)) <= thicknessX && sqrt(pow(dY, 2)) <= thicknessY)
	{
		m_spOwner->GetComponent<C_Health>()->Damage();
		return true;
	}
	return false;
}