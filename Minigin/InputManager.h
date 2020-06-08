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
		ButtonY
	};
	enum class KeyboardButton
	{
		ButtonSpace,
		ButtonB,
		ButtonX,
		ButtonY,
		ButtonEsc
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		bool IsPressed(KeyboardButton button) const;
		Command* HandleInput();
	private:
		friend class Singleton<InputManager>;
		InputManager() = default;
		XINPUT_STATE m_CurrentState{};


		std::unique_ptr<FireCommand> m_Fire{ std::make_unique<FireCommand>() };
	};

}
