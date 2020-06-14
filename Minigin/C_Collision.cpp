#include "MiniginPCH.h"
#include "C_Collision.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "PlayerState.h"
#include "../BubbleBobble/Maita.h"
#include "../BubbleBobble/ZenChan.h"
#include "../BubbleBobble/Boulder.h"
#include "../BubbleBobble/Collectable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LevelManager.h"
#include "C_Score.h"
#include "C_Collectable.h"
#include "C_ZenChanBehaviour.h"
#include "C_Health.h"
#include "C_BubbleBehaviour.h"
#include "C_InputHandling.h"
#include "C_Sprite.h"
#include "C_Movement.h"

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
	// get collision boxes
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

	// if collides
	if (sqrt(pow(dX, 2)) <= thicknessX && sqrt(pow(dY, 2)) <= thicknessY)
	{
		// other is maita
		if (dynamic_cast<Maita*>(other))
		{
			if (other->GetComponent<C_BubbleBehaviour>()->GetIsBubbled())
			{
				auto go = std::make_shared<Collectable>(2, m_spOwner->m_Transform.GetPosition().x, m_spOwner->m_Transform.GetPosition().y);
				LevelManager::GetInstance().GetCollectables().push_back(go);
				SceneManager::GetInstance().GetCurrentScene().Add(go);
				other->destroy();
				return true;
			}
		}
		// other is zenchan
		else if (dynamic_cast<ZenChan*>(other))
		{
			if (other->GetComponent<C_BubbleBehaviour>()->GetIsBubbled())
			{
				auto go = std::make_shared<Collectable>(1, m_spOwner->m_Transform.GetPosition().x, m_spOwner->m_Transform.GetPosition().y);
				LevelManager::GetInstance().GetCollectables().push_back(go);
				SceneManager::GetInstance().GetCurrentScene().Add(go);
				other->destroy();
				return true;
			}
			else
			{
				m_spOwner->GetComponent<C_Health>()->Damage();
				other->GetComponent<C_ZenChanBehaviour>()->RemoveTarget();
			}
		}
		// other is block collision removed from bottom side
		else if(dY < thicknessY)
		{
				// from left
				if (dX < 0.0f)
				{
					m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x -
						m_spOwner->GetComponent<C_Movement>()->GetSpeed() * 1.0f * TimeManager::GetInstance().GetDeltaTime(),
						m_spOwner->m_Transform.GetPosition().y);
				}
				// from right
				else if (dX > 0.0f)
				{
					m_spOwner->SetPosition(m_spOwner->m_Transform.GetPosition().x +
						m_spOwner->GetComponent<C_Movement>()->GetSpeed() * 1.0f * TimeManager::GetInstance().GetDeltaTime(),
						m_spOwner->m_Transform.GetPosition().y);

				}
				// from top
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

bool dae::C_Collision::CheckCollisionToFall(GameObject* other) // determines wether there are blocks underneath to hold from falling
{
	// get collision boxes
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

	// collides
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
	// get collision boxes
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

	// collides
	if (sqrt(pow(dX, 2)) <= thicknessX && sqrt(pow(dY, 2)) <= thicknessY)
	{
		m_spOwner->GetComponent<C_Health>()->Damage();
		return true;
	}
	return false;
}

bool dae::C_Collision::HitCollectable(Collectable* collectable)
{
	// get collision boxes
	float width{ m_spOwner->GetComponent<C_Sprite>()->GetWidth() };
	float height{ m_spOwner->GetComponent<C_Sprite>()->GetHeight() };
	float posX{ m_spOwner->m_Transform.GetPosition().x };
	float posY{ m_spOwner->m_Transform.GetPosition().y };

	float otherWidth{ collectable->GetComponent<C_Sprite>()->GetWidth() };
	float otherHeight{ collectable->GetComponent<C_Sprite>()->GetHeight() };
	float otherPosX{ collectable->m_Transform.GetPosition().x };
	float otherPosY{ collectable->m_Transform.GetPosition().y };

	float dX = (posX + width / 2) - (otherPosX + otherWidth / 2);
	float dY = (posY + height / 2) - (otherPosY + otherHeight / 2);

	float thicknessX = width / 2 + otherWidth / 2;
	float thicknessY = height / 2 + otherHeight / 2;

	// collides
	if (sqrt(pow(dX, 2)) <= thicknessX && sqrt(pow(dY, 2)) <= thicknessY)
	{
		m_spOwner->GetComponent<C_Score>()->Add(collectable->GetComponent<C_Collectable>()->GetPoints());
		return true;
	}
	return false;
}

