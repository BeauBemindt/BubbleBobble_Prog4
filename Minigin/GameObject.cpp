#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (size_t i{}; i < m_spComponents.size(); ++i)
	{
		m_spComponents[i]->Update();
	}
}

void dae::GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();
	if (m_Texture)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
	for (size_t i{}; i < m_spComponents.size(); ++i)
	{
		m_spComponents[i]->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
