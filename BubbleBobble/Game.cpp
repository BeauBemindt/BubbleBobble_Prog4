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
#include "C_FPS.h"
#include "O_Test.h"
#include "C_Subject.h"
#include "C_Movement.h"
#include "C_InputHandling.h"
#include "C_Collision.h"
#include "PlayerCharacter.h"
#include "Block.h"

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
		480,
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
	auto& scene = SceneManager::GetInstance().CreateScene("TestLevel");

	// tests
	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<PlayerCharacter>();
	m_Player = go.get();
	scene.Add(go);
	go = std::make_shared<Block>();
	m_Block = go.get();
	scene.Add(go);
	go = std::make_shared<Block>();
	m_Block2 = go.get();
	m_Block2->SetPosition(150, 150);
	scene.Add(go);

	auto fps = std::make_shared<GameObject>();
	auto frames = fps->AddComponent<dae::C_FPS>();
	auto observer = go->AddComponent<dae::O_Test>();
	auto subject = fps->AddComponent<dae::C_Subject>();
	subject->attach(observer);
	scene.Add(fps);
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

		bool doContinue = true;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();

			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();
			time.Update();

			m_Block->GetComponent<C_Collision>()->HandleCollision(m_Player);
			m_Block2->GetComponent<C_Collision>()->HandleCollision(m_Player);

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}