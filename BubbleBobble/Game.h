#pragma once
#include "GameObject.h"

struct SDL_Window;
namespace dae
{
	class Game
	{
	public:
		void Initialize();
		void LoadGame();
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		GameObject* m_Player{};
		GameObject* m_Block{};
		GameObject* m_Block2{};
	};
}

