#pragma once
#include "Singleton.h"

namespace dae
{
	class Block;
	class PlayerCharacter;
	class ZenChan;
	class Maita;
	class Scene;
	class LevelManager : public Singleton<LevelManager>
	{
	public:
		void Update();
		void LoadLevel(const std::string& filepath, Scene* scene);
		void SetPlayerAmount(int amount);
		std::vector<std::shared_ptr<Block>> GetLevel();
		std::vector<std::shared_ptr<PlayerCharacter>> GetPlayers();
		std::vector<std::shared_ptr<Maita>> GetMaita();
		std::vector<std::shared_ptr<ZenChan>> GetZenChan();
	private:
		void HandleCollision();

		std::vector<std::shared_ptr<Block>> m_Blocks{};
		std::vector<std::shared_ptr<PlayerCharacter>> m_Players{};
		std::vector<std::shared_ptr<Maita>> m_Maitas{};
		std::vector<std::shared_ptr<ZenChan>> m_ZenChans{};
		int m_PlayerAmount{};
	};
}

