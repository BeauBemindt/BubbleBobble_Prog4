#include "MiniginPCH.h"
#include "C_Collision.h"
#include "GameObject.h"
#include "C_Sprite.h"
#include "C_Movement.h"
#include "TimeManager.h"

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

void dae::C_Collision::HandleCollision(GameObject* other)
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
		if (sqrt(pow(sqrt(pow(dX, 2)) - thicknessX, 2)) <= 2.0f)
		{
			if (dX < 0)
			{
				other->SetPosition(other->m_Transform.GetPosition().x +
					other->GetComponent<C_Movement>()->GetSpeed() * TimeManager::GetInstance().GetDeltaTime(), other->m_Transform.GetPosition().y);
			}
			else if (dX > 0)
			{
				other->SetPosition(other->m_Transform.GetPosition().x -
					other->GetComponent<C_Movement>()->GetSpeed() * TimeManager::GetInstance().GetDeltaTime(), other->m_Transform.GetPosition().y);
			}
		}
		else
		{
			if (dY > 0)
			{
				other->SetPosition(other->m_Transform.GetPosition().x,
					other->m_Transform.GetPosition().y - other->GetComponent<C_Movement>()->GetGravity() * TimeManager::GetInstance().GetDeltaTime());
				other->GetComponent<C_Movement>()->EndJumping();
			}
			else if (dY < 0)
			{
				other->SetPosition(other->m_Transform.GetPosition().x,
					other->m_Transform.GetPosition().y + other->GetComponent<C_Movement>()->GetGravity() * TimeManager::GetInstance().GetDeltaTime());
				other->GetComponent<C_Movement>()->Fall();
			}
		}
	}
}
