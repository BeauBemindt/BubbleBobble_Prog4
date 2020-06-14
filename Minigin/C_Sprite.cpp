#include "MiniginPCH.h"
#include "Renderer.h"
#include "C_Sprite.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TimeManager.h"

dae::C_Sprite::C_Sprite(GameObject* owner)
	: Component(owner)
	, m_Texture{}
	, m_Width{32}
	, m_Height{32}
	, m_PosX{m_spOwner->m_Transform.GetPosition().x}
	, m_PosY{ m_spOwner->m_Transform.GetPosition().y}
	, m_Rect{}
	, m_AnimationTimer{}
	, m_Pause{}
{
}

void dae::C_Sprite::Update()
{
	m_PosX = m_spOwner->m_Transform.GetPosition().x;
	m_PosY = m_spOwner->m_Transform.GetPosition().y;

	if (!m_Pause) // if not paused, update animation
	{
		m_AnimationTimer += TimeManager::GetInstance().GetDeltaTime();

		if (AnimationTimeReached())
		{
			int x = m_Rect.x + 34;
			if (x > 256)
			{
				x = 0;
			}
			m_Rect.x = x;
		}
	}

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
	m_Pause = false;
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

float dae::C_Sprite::GetWidth() const
{
	return m_Width;
}

float dae::C_Sprite::GetHeight() const
{
	return m_Height;
}

void dae::C_Sprite::Pause()
{
	m_Pause = true;
}
