#include "MiniginPCH.h"
#include "C_Bubble.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "C_Movement.h"

dae::C_Bubble::C_Bubble(GameObject* owner)
	: Component(owner)
	, m_Timer{0.0f}
{
}

void dae::C_Bubble::Update()
{
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
