#include "MiniginPCH.h"
#include "LevelManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Scene.h"
#include "../BubbleBobble/Block.h"
#include "../BubbleBobble/PlayerCharacter.h"
#include "../BubbleBobble/Maita.h"
#include "../BubbleBobble/ZenChan.h"
#include "C_Collision.h"
#include "C_EnemyCollision.h"
#include "C_InputHandling.h"
#include "PlayerState.h"
#include "C_Movement.h"
#include "C_MaitaBehaviour.h"
#include "C_Health.h"

void dae::LevelManager::Update()
{
	for (size_t i{}; i < m_Players.size(); ++i)
	{
		if (m_Players[i]->GetComponent<C_Health>()->GetHealth() <= 0)
		{
			//int nr{ m_spOwner->GetComponent<C_Player>()->GetNumber() };
			m_Players[i]->destroy();
			m_Players.erase(m_Players.begin() + i);
		}
	}
	HandleCollision();
}

void dae::LevelManager::LoadLevel(const std::string& filepath, Scene* scene)
{
	float posX{};
	float posY{};
	std::string line;
	std::ifstream myfile("../Data/" + filepath);
	int players{};
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			for (auto l : line)
			{
				if (l == '1')
				{
					m_Blocks.push_back(std::make_shared<Block>());
					m_Blocks[m_Blocks.size() - 1]->SetPosition(32 * posX, 32 * posY);
					scene->Add(m_Blocks[m_Blocks.size() - 1]);
				}
				else if (l == '2')
				{
					m_Maitas.push_back(std::make_shared<Maita>());
					m_Maitas[m_Maitas.size() - 1]->SetPosition(32 * posX, 32 * posY);
					scene->Add(m_Maitas[m_Maitas.size() - 1]);
				}
				else if (l == '3')
				{
					m_ZenChans.push_back(std::make_shared<ZenChan>());
					m_ZenChans[m_ZenChans.size() - 1]->SetPosition(32 * posX, 32 * posY);
					scene->Add(m_ZenChans[m_ZenChans.size() - 1]);
				}
				else if (l == '4' && players < m_PlayerAmount)
				{
					m_Players.push_back(std::make_shared<PlayerCharacter>(players + 1));
					m_Players[m_Players.size() - 1]->SetPosition(32 * posX, 32 * posY);
					scene->Add(m_Players[m_Players.size() - 1]);
					++players;
				}
				++posX;
			}
			++posY;
			posX = 0;
		}
		myfile.close();
	}
}

void dae::LevelManager::HandleCollision()
{
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

std::vector<std::shared_ptr<dae::Block>> dae::LevelManager::GetLevel()
{
	return m_Blocks;
}

std::vector<std::shared_ptr<dae::PlayerCharacter>> dae::LevelManager::GetPlayers()
{
	return m_Players;
}

std::vector<std::shared_ptr<dae::Maita>> dae::LevelManager::GetMaita()
{
	return m_Maitas;
}

std::vector<std::shared_ptr<dae::ZenChan>> dae::LevelManager::GetZenChan()
{
	return m_ZenChans;
}
