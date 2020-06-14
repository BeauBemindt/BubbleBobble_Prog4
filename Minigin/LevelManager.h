#pragma once
#include "Singleton.h"

namespace dae
{
	class Block;
	class PlayerCharacter;
	class ZenChan;
	class Maita;
	class Scene;
	class Collectable;
	class LevelManager : public Singleton<LevelManager>
	{
	public:
		void Update();
		void LoadLevel(int number, Scene* scene);
		void LoadStartingMenu();
		bool CheckGameOver();
		bool IsInGame() const;
		void ClearLevel();
		void SetPlayerAmount(int amount);
		void StartGame(int players);
		std::vector<std::shared_ptr<Block>>& GetLevel();
		std::vector<std::shared_ptr<PlayerCharacter>>& GetPlayers();
		std::vector<std::shared_ptr<Maita>>& GetMaita();
		std::vector<std::shared_ptr<ZenChan>>& GetZenChan();
		std::vector<std::shared_ptr<Collectable>>& GetCollectables();
	private:
		void HandleCollision();

		std::vector<std::shared_ptr<Block>> m_Blocks{};
		std::vector<std::shared_ptr<PlayerCharacter>> m_Players{};
		std::vector<std::shared_ptr<Maita>> m_Maitas{};
		std::vector<std::shared_ptr<ZenChan>> m_ZenChans{};
		std::vector<std::shared_ptr<Collectable>> m_Collectable{};
		int m_PlayerAmount{};
		int m_CurrentLevel{1};
		bool m_InGame{};
	};
}

