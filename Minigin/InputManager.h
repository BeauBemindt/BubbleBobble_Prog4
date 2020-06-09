#pragma once
#include <XInput.h>
#include <memory>
#include "Command.h"
#include "Singleton.h"

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

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		std::vector<Command*>& HandleInput();

	private:
		friend class Singleton<InputManager>;
		InputManager() = default;
		XINPUT_STATE m_CurrentState{};
		std::vector<Command*> m_Commands;

		std::unique_ptr<FireCommand> m_Fire{ std::make_unique<FireCommand>() };
		std::unique_ptr<MoveRightCommand> m_MoveRight{ std::make_unique<MoveRightCommand>() };
		std::unique_ptr<MoveLeftCommand> m_MoveLeft{ std::make_unique<MoveLeftCommand>() };
		std::unique_ptr<JumpCommand> m_Jump{ std::make_unique<JumpCommand>() };
	};

}
