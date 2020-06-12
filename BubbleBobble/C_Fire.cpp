#include "MiniginPCH.h"
#include "C_Fire.h"
#include "TimeManager.h"
#include "../BubbleBobble/Bubble.h"
#include "SceneManager.h"
#include "Scene.h"

dae::C_Fire::C_Fire(GameObject* owner)
	: Component(owner)
{
}

void dae::C_Fire::Update()
{
	m_Timer += TimeManager::GetInstance().GetDeltaTime();
}

void dae::C_Fire::Render() const
{
}

void dae::C_Fire::Fire(float dir)
{
	if (m_Timer >= 1.0f)
	{
		auto go = std::make_shared<Bubble>(m_spOwner->m_Transform.GetPosition().x + object->GetComponent<C_Sprite>()->GetWidth()
			, object->m_Transform.GetPosition().y + object->GetComponent<C_Sprite>()->GetHeight() / 2, object, 1.0f);
		SceneManager::GetInstance().GetCurrentScene().Add(go);
	}
}
