#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderClipTexture(const Texture2D& texture, const float x, const float y, const SDL_Rect* clip = nullptr);
		void RenderClipTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, const SDL_Rect* clip = nullptr);

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
	};
}

