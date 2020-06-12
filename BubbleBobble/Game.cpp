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
#include "LevelManager.h"
#include "C_Player.h"

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
	//go->SetTexture("background.jpg");
	//scene.Add(go);

	go = std::make_shared<PlayerCharacter>(1);
	m_Player = go.get();
	scene.Add(go);

	go = std::make_shared<PlayerCharacter>(2);
	m_Player2 = go.get();
	m_Player2->m_Transform.SetPosition(350.0f, 50.0f, 0.0f);
	scene.Add(go);

	LevelManager::GetInstance().LoadLevel("Level1.txt", &scene);

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
		auto& level = LevelManager::GetInstance();

		bool doContinue = true;
		bool collide{ false };
		bool collision{ false };
		bool collide2{ false };
		bool collision2{ false };
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();

			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();
			time.Update();

			collide = false;
			collision = false;

			for (auto block : level.GetLevel())
			{
				if (collide = m_Player->GetComponent<C_Collision>()->HandleCollision(block.get()))
				{
					collision = collide;
				}
			}
			if (!collision)
			{
				for (auto block : level.GetLevel())
				{
					if (collide = m_Player->GetComponent<C_Collision>()->CheckCollisionToFall(block.get()))
					{
						break;
					}
				}
				if (!collide && m_Player->GetComponent<C_InputHandling>()->GetState()->m_ID == State::stateID::Running)
				{
					m_Player->GetComponent<C_InputHandling>()->GetState()->OnExit(m_Player);
					m_Player->GetComponent<C_InputHandling>()->SetState(new FallingState());
					m_Player->GetComponent<C_InputHandling>()->GetState()->OnEnter(m_Player);
				}
			}

			collide2 = false;
			collision2 = false;

			for (auto block : level.GetLevel())
			{
				if (collide2 = m_Player2->GetComponent<C_Collision>()->HandleCollision(block.get()))
				{
					collision2 = collide2;
				}
			}
			if (!collision2)
			{
				for (auto block : level.GetLevel())
				{
					if (collide2 = m_Player2->GetComponent<C_Collision>()->CheckCollisionToFall(block.get()))
					{
						break;
					}
				}
				if (!collide2 && m_Player2->GetComponent<C_InputHandling>()->GetState()->m_ID == State::stateID::Running)
				{
					m_Player2->GetComponent<C_InputHandling>()->GetState()->OnExit(m_Player2);
					m_Player2->GetComponent<C_InputHandling>()->SetState(new FallingState());
					m_Player2->GetComponent<C_InputHandling>()->GetState()->OnEnter(m_Player2);
				}
			}

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}