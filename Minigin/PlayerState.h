#pragma once
#include "Component.h"
#include "State.h"

namespace dae
{
	class Command;
	class JumpingState;
	class RunningState;
	class PlayerState
	{
	public:

		static JumpingState m_JumpingState;
		static RunningState m_RunningState;

		virtual void Update() = 0;
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual void HandleInput(GameObject* owner) = 0;
	protected:
		std::vector<Command*> m_Commands;
		State::stateID m_ID{};
	};

	class JumpingState : public PlayerState
	{
	public:
		void Update() override;
		void OnEnter() override;
		void OnExit() override;
		void HandleInput(GameObject* owner) override;
	};

	class RunningState : public PlayerState
	{
	public:
		void Update() override;
		void OnEnter() override;
		void OnExit() override;
		void HandleInput(GameObject* owner) override;
	};
}

