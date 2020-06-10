#pragma once
#include <XInput.h>
#include <memory>
#include "Singleton.h"
#include "State.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		ButtonRight,
		ButtonLeft
	};
	enum class KeyboardButton
	{
		ButtonSpace,
		ButtonDown,
		ButtonX,
		ButtonY,
		ButtonEsc
	};

	class Command;
	class FireCommand;
	class MoveRightCommand;
	class MoveLeftCommand;
	class JumpCommand;
	class StandStillCommand;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		std::vector<Command*>& HandleInput(State::stateID id);

	private:
		friend class Singleton<InputManager>;
		InputManager();
		XINPUT_STATE m_CurrentState{};
		std::vector<Command*> m_Commands;

		std::unique_ptr<FireCommand> m_Fire;
		std::unique_ptr<MoveRightCommand> m_MoveRight;
		std::unique_ptr<MoveLeftCommand> m_MoveLeft;
		std::unique_ptr<JumpCommand> m_Jump;
		std::unique_ptr<StandStillCommand> m_StandStill;
	};

}
