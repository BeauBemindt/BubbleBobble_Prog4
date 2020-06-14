#include "MiniginPCH.h"
#include "LevelManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include "SceneManager.h"
#include "Scene.h"
#include "../BubbleBobble/Block.h"
#include "../BubbleBobble/PlayerCharacter.h"
#include "../BubbleBobble/Maita.h"
#include "../BubbleBobble/ZenChan.h"
#include "../BubbleBobble/Collectable.h"
#include "C_Collision.h"
#include "C_EnemyCollision.h"
#include "C_InputHandling.h"
#include "PlayerState.h"
#include "C_Movement.h"
#include "C_MaitaBehaviour.h"
#include "C_Health.h"
#include "C_Collectable.h"
#include "C_StartScreen.h"

void dae::LevelManager::Update()
{

	// in menu or playing
	if (m_InGame)
	{
		// if players died
		if (CheckGameOver())
		{
			ClearLevel();
			for (auto player : m_Players)
			{
				player->destroy();
			}
			m_Players.clear();
			LoadStartingMenu();
		}
		// if lever is cleared ->  go to next level
		else if (m_Maitas.size() <= 0 && m_ZenChans.size() <= 0 && m_Collectable.size() <= 0)
		{
			ClearLevel();
			++m_CurrentLevel;
			if (m_CurrentLevel > 3)
			{
				m_Players.clear();
				LoadStartingMenu();
			}
			else
			{
				LoadLevel(m_CurrentLevel, &SceneManager::GetInstance().GetCurrentScene());
			}
		}
		else
		{
			HandleCollision();
		}
	}
}

void dae::LevelManager::LoadLevel(int number, Scene* scene)
{
	// load level from file
	float posX{};
	float posY{};
	std::string line;
	std::string filePath{ "../Data/Level"};
	filePath += std::to_string(number);
	filePath += ".txt";
	std::ifstream myfile(filePath);
	size_t players{m_Players.size()};
	size_t playersSet{};
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			for (auto l : line)
			{
				if (l == '1')
				{
					m_Blocks.push_back(std::make_shared<Block>());
					m_Blocks[m_Blocks.size() - 1]->SetPosition(32 * posX,100 + 32 * posY);
					scene->Add(m_Blocks[m_Blocks.size() - 1]);
				}
				else if (l == '2')
				{
					m_Maitas.push_back(std::make_shared<Maita>());
					m_Maitas[m_Maitas.size() - 1]->SetPosition(32 * posX, 100 + 32 * posY);
					scene->Add(m_Maitas[m_Maitas.size() - 1]);
				}
				else if (l == '3')
				{
					m_ZenChans.push_back(std::make_shared<ZenChan>());
					m_ZenChans[m_ZenChans.size() - 1]->SetPosition(32 * posX, 100 + 32 * posY);
					scene->Add(m_ZenChans[m_ZenChans.size() - 1]);
				}
				else if (l == '4')
				{
					if(players == size_t(1))
					{
						m_Players[0]->SetPosition(32 * posX, 100 + 32 * posY);
					}
					else if (players == size_t(2))
					{
						m_Players[playersSet]->SetPosition(32 * posX, 100 + 32 * posY);
						++playersSet;
					}
					else if (m_Players.size() < size_t(m_PlayerAmount))
					{
						m_Players.push_back(std::make_shared<PlayerCharacter>(int(m_Players.size()) + 1));
						m_Players[m_Players.size() - 1]->SetPosition(32 * posX, 100 + 32 * posY);
						scene->Add(m_Players[m_Players.size() - 1]);
					}
				}
				++posX;
			}
			++posY;
			posX = 0;
		}
		myfile.close();
	}
}

void dae::LevelManager::LoadStartingMenu()
{
	m_InGame = false;
	m_Players.push_back(std::make_shared<PlayerCharacter>(1));
	m_Players[m_Players.size() - 1]->SetPosition(-100, -100);
	SceneManager::GetInstance().GetCurrentScene().Add(m_Players[m_Players.size() - 1]);
	auto go = std::make_shared<GameObject>();
	go->AddComponent<C_StartScreen>();
	SceneManager::GetInstance().GetCurrentScene().Add(go);
}

bool dae::LevelManager::CheckGameOver()
{
	// if player has no health -> remove player
	for (size_t i{}; i < m_Players.size(); ++i)
	{
		if (m_Players[i]->GetComponent<C_Health>()->GetHealth() <= 0)
		{
			m_Players[i]->destroy();
			m_Players.erase(m_Players.begin() + i);
		}
	};
	// if players are all dead -> end game
	if (m_Players.size() <= 0)
	{
		return true;
	}
	return false;
}

bool dae::LevelManager::IsInGame() const
{
	return m_InGame;
}

void dae::LevelManager::ClearLevel()
{
	for (auto block : m_Blocks)
	{
		block->destroy();
	}
	m_Blocks.clear();
	//for (auto player : m_Players)
	//{
	//	player->destroy();
	//}
	//m_Players.clear();
	for (auto maita : m_Maitas)
	{
		maita->destroy();
	}
	m_Maitas.clear();
	for (auto zenchan : m_ZenChans)
	{
		zenchan->destroy();
	}
	m_ZenChans.clear();
	for (auto collectable : m_Collectable)
	{
		collectable->destroy();
	}
	m_Collectable.clear();
}

void dae::LevelManager::HandleCollision()
{
	// Handle collision between all level objects
	bool collide{ false };
	bool collision{ false };

	// players collision
	for (size_t i{}; i < m_Players.size(); ++i)
	{
		for (auto block : GetLevel())
		{
			if (collide = m_Players[i]->GetComponent<C_Collision>()->HandleCollision(block.get()))
			{
				collision = collide;
			}
		}
		if (!collision)
		{
			for (auto block : GetLevel())
			{
				if (collide = m_Players[i]->GetComponent<C_Collision>()->CheckCollisionToFall(block.get()))
				{
					break;
				}
			}
			if (!collide && m_Players[i]->GetComponent<C_InputHandling>()->GetState()->m_ID == State::stateID::Running)
			{
				m_Players[i]->GetComponent<C_InputHandling>()->GetState()->OnExit(m_Players[i].get());
				m_Players[i]->GetComponent<C_InputHandling>()->SetState(new FallingState());
				m_Players[i]->GetComponent<C_InputHandling>()->GetState()->OnEnter(m_Players[i].get());
			}
		}
		for (size_t j{}; j < m_Maitas.size(); ++j)
		{
			if (m_Players[i]->GetComponent<C_Collision>()->HandleCollision(m_Maitas[j].get()))
			{
				m_Maitas.erase(m_Maitas.begin() + j);
			}
		}
		for (size_t j{}; j < m_ZenChans.size(); ++j)
		{
			if (m_Players[i]->GetComponent<C_Collision>()->HandleCollision(m_ZenChans[j].get()))
			{
				m_ZenChans.erase(m_ZenChans.begin() + j);
			}
		}
		for (size_t j{}; j < m_Collectable.size(); ++j)
		{
			if (m_Collectable[j]->GetComponent<C_Collectable>()->Collision(m_Players[i].get()))
			{
				m_Collectable.erase(m_Collectable.begin() + j);
			}
		}
	}

	//enemy collision
	collision = false;
	collide = false;
	for (auto maita : m_Maitas)
	{
		for (auto block : GetLevel())
		{
			if (collide = maita->GetComponent<C_EnemyCollision>()->HandleCollision(block.get()))
			{
				collision = collide;
			}
		}
		if (!collision)
		{
			for (auto block : GetLevel())
			{
				if (collide = maita->GetComponent<C_EnemyCollision>()->CheckCollisionToFall(block.get()))
				{
					break;
				}
			}
			if (!collide)
			{
				maita->GetComponent<C_Movement>()->Fall(1.0f);
			}
		}
	}
	collision = false;
	collide = false;
	for (auto zenChan : m_ZenChans)
	{
		for (auto block : GetLevel())
		{
			if (collide = zenChan->GetComponent<C_EnemyCollision>()->HandleCollision(block.get()))
			{
				collision = collide;
			}
		}
		if (!collision)
		{
			for (auto block : GetLevel())
			{
				if (collide = zenChan->GetComponent<C_EnemyCollision>()->CheckCollisionToFall(block.get()))
				{
					break;
				}
			}
			if (!collide)
			{
				zenChan->GetComponent<C_Movement>()->Fall(1.0f);
			}
		}
	}
}

void dae::LevelManager::SetPlayerAmount(int amount)
{
	m_PlayerAmount = amount;
}

void dae::LevelManager::StartGame(int players)
{
	// start new game from level 1
	for (auto player : m_Players)
	{
		player->destroy();
	}
	m_Players.clear();
	m_PlayerAmount = players;
	LoadLevel(1, &SceneManager::GetInstance().GetCurrentScene());
	m_InGame = true;
}

std::vector<std::shared_ptr<dae::Block>>& dae::LevelManager::GetLevel()
{
	return m_Blocks;
}

std::vector<std::shared_ptr<dae::PlayerCharacter>>& dae::LevelManager::GetPlayers()
{
	return m_Players;
}

std::vector<std::shared_ptr<dae::Maita>>& dae::LevelManager::GetMaita()
{
	return m_Maitas;
}

std::vector<std::shared_ptr<dae::ZenChan>>& dae::LevelManager::GetZenChan()
{
	return m_ZenChans;
}

std::vector<std::shared_ptr<dae::Collectable>>& dae::LevelManager::GetCollectables()
{
	return m_Collectable;
}
