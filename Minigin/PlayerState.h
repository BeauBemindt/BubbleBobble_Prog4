#pragma once
#include "Component.h"
#include "State.h"

namespace dae
{
	class Command;
	class PlayerState
	{
	public:
		virtual ~PlayerState() = default;
		virtual void Update(GameObject* owner) = 0;
		virtual void OnEnter(GameObject* owner) = 0;
		virtual void OnExit(GameObject* owner) = 0;
		virtual void HandleInput(GameObject* owner) = 0;

		State::stateID m_ID{};
		float m_Timer{};
	protected:
		std::vector<Command*> m_Commands;
	};

	class JumpingState : public PlayerState
	{
	public:
		void Update(GameObject* owner) override;
		void OnEnter(GameObject* owner) override;
		void OnExit(GameObject* owner) override;
		void HandleInput(GameObject* owner) override;

	private:
	};

	class RunningState : public PlayerState
	{
	public:
		void Update(GameObject* owner) override;
		void OnEnter(GameObject* owner) override;
		void OnExit(GameObject* owner) override;
		void HandleInput(GameObject* owner) override;
	};

	class FallingState : public PlayerState
	{
	public:
		void Update(GameObject* owner) override;
		void OnEnter(GameObject* owner) override;
		void OnExit(GameObject* owner) override;
		void HandleInput(GameObject* owner) override;
	};
}

