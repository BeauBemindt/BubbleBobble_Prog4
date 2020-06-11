#include "MiniginPCH.h"
#include "LevelManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Scene.h"

void dae::LevelManager::Update()
{
}

void dae::LevelManager::LoadLevel(const std::string& filepath, Scene* scene)
{
	float posX{};
	float posY{};
	std::string line;
	std::ifstream myfile("../Data/" + filepath);
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
				++posX;
			}
			++posY;
			posX = 0;
		}
		myfile.close();
	}
}

std::vector<std::shared_ptr<dae::Block>> dae::LevelManager::GetLevel()
{
	return m_Blocks;
}
