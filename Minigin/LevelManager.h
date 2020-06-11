#pragma once
#include "Singleton.h"
#include "../BubbleBobble/Block.h"

namespace dae
{
	class Scene;
	class LevelManager : public Singleton<LevelManager>
	{
	public:
		void Update();
		void LoadLevel(const std::string& filepath, Scene* scene);
		std::vector<std::shared_ptr<Block>> GetLevel();
	private:
		std::vector<std::shared_ptr<Block>> m_Blocks{};
	};
}

