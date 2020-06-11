#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <SDL.h>

namespace dae
{
	class C_Sprite : public Component
	{
	public:
		C_Sprite(GameObject* owner);
		void Update() override;
		void Render() const override;
		void SetTexture(const std::string& filename);
		void Scale(float scale);
		void SetRect(float x, float y, float width, float height);
		SDL_Rect GetRect() const;
		bool AnimationTimeReached();
		float GetWidth() const;
		float GetHeight() const;
	private:
		std::shared_ptr<Texture2D> m_Texture;
		float m_Width;
		float m_Height;
		float m_PosX;
		float m_PosY;
		SDL_Rect m_Rect;
		float m_AnimationTimer;
	};
}

