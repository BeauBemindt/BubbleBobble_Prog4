#include "MiniginPCH.h"
#include "Renderer.h"
#include "C_Sprite.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TimeManager.h"

dae::C_Sprite::C_Sprite(GameObject* owner)
	: Component(owner)
	, m_Texture{}
	, m_Width{100}
	, m_Height{100}
	, m_PosX{m_spOwner->m_Transform.GetPosition().x}
	, m_PosY{ m_spOwner->m_Transform.GetPosition().y}
	, m_Rect{}
	, m_AnimationTimer{}
{
}

void dae::C_Sprite::Update()
{
	m_PosX = m_spOwner->m_Transform.GetPosition().x;
	m_PosY = m_spOwner->m_Transform.GetPosition().y;
	m_AnimationTimer += TimeManager::GetInstance().GetDeltaTime();
}

void dae::C_Sprite::Render() const
{
	Renderer::GetInstance().RenderClipTexture(*m_Texture, m_PosX, m_PosY, m_Width, m_Height, &m_Rect);
}

void dae::C_Sprite::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::C_Sprite::Scale(float scale)
{
	m_Width *= scale;
	m_Height *= scale;
}

void dae::C_Sprite::SetRect(float x, float y, float width, float height)
{
	m_Rect.x = static_cast<int>(x);
	m_Rect.y = static_cast<int>(y);
	m_Rect.w = static_cast<int>(width);
	m_Rect.h = static_cast<int>(height);
}

SDL_Rect dae::C_Sprite::GetRect() const
{
	return m_Rect;
}

bool dae::C_Sprite::AnimationTimeReached()
{
	if (m_AnimationTimer >= 0.1f)
	{
		m_AnimationTimer = 0.0f;
		return true;
	}
	return false;
}
