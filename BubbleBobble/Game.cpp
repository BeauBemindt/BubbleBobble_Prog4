#include "MiniginPCH.h"
#include "Game.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "PlayerCharacter.h"
#include "Maita.h"
#include "LevelManager.h"
#include "C_FPS.h"
#include "O_Test.h"
#include "C_Subject.h"
#include "C_Movement.h"
#include "C_InputHandling.h"
#include "C_Collision.h"
#include "C_Player.h"
#include "C_MaitaBehaviour.h"
#include "C_enemyCollision.h"

using namespace std;
using namespace std::chrono;

void dae::Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		580,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Game::LoadGame()
{
	SceneManager::GetInstance().CreateScene("TestLevel");

	LevelManager::GetInstance().LoadStartingMenu();

}

void dae::Game::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Game::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = TimeManager::GetInstance();
		auto& level = LevelManager::GetInstance();

		bool doContinue = true;

		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();

			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();
			time.Update();
			level.Update();

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

