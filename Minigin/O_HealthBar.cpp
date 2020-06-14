#include "MiniginPCH.h"
#include "O_HealthBar.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "C_Health.h"
#include "C_Player.h"

dae::O_HealthBar::O_HealthBar(GameObject* owner)
	: C_Observer(owner)
	, m_Textures{}
{
	for (int i{}; i < m_spOwner->GetComponent<C_Health>()->GetHealth(); ++i)
	{
		m_Textures.push_back(ResourceManager::GetInstance().LoadTexture("Health.png"));
	}
}

void dae::O_HealthBar::Notify(EVENT event)
{
	if (event == EVENT::damaged)
	{
		m_Textures.pop_back();
	}
}

void dae::O_HealthBar::Update()
{
}

void dae::O_HealthBar::Render() const
{
	for (int i{}; i < m_spOwner->GetComponent<C_Health>()->GetHealth(); ++i)
	{
		Renderer::GetInstance().RenderTexture(*m_Textures[i], (m_spOwner->GetComponent<C_Player>()->GetNumber() - 1) * 410.0f + 16.0f * (i + 1), 16.0f);
	}
}