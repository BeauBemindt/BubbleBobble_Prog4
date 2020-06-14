#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"

dae::InputManager::InputManager()
	: m_Fire{std::make_unique<FireCommand>()}
	, m_Jump{std::make_unique<JumpCommand>()}
	, m_MoveLeft{ std::make_unique<MoveLeftCommand>() }
	, m_MoveRight{ std::make_unique<MoveRightCommand>() }
	, m_StandStill{ std::make_unique<StandStillCommand>() }
	, m_StartSingle{std::make_unique<StartSingleCommand>()}
	, m_StartCoOp{ std::make_unique<StartCoOpCommand>() }
{

}

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::ButtonRight:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::ButtonLeft:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	default: return false;
	}
}

std::vector<dae::Command*>& dae::InputManager::HandleInput(State::stateID id, int playerNbr)
{
	m_Commands.clear();
	// player 1
	if (playerNbr == 1)
	{
		if (IsPressed(ControllerButton::ButtonRight))
		{
			m_Commands.push_back(m_MoveRight.get());
		}
		else if (IsPressed(ControllerButton::ButtonLeft))
		{
			m_Commands.push_back(m_MoveLeft.get());
		}
		else
		{
			m_Commands.push_back(m_StandStill.get());
		}
		if (IsPressed(ControllerButton::ButtonX))
		{
			m_Commands.push_back(m_Fire.get());
		}
		if (id == State::stateID::Running)
		{
			if (IsPressed(ControllerButton::ButtonA))
			{
				m_Commands.push_back(m_Jump.get());
			}
		}
		if (!LevelManager::GetInstance().IsInGame())
		{
			if (IsPressed(ControllerButton::ButtonY))
			{
				m_Commands.push_back(m_StartSingle.get());
			}
			else if (IsPressed(ControllerButton::ButtonB))
			{
				m_Commands.push_back(m_StartCoOp.get());
			}
		}
	}

	// player 2
	if (playerNbr == 2)
	{
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		if (keystate[SDL_SCANCODE_RIGHT])
		{
			m_Commands.push_back(m_MoveRight.get());
		}
		else if (keystate[SDL_SCANCODE_LEFT])
		{
			m_Commands.push_back(m_MoveLeft.get());
		}
		else
		{
			m_Commands.push_back(m_StandStill.get());
		}
		if (keystate[SDL_SCANCODE_RSHIFT])
		{
			m_Commands.push_back(m_Fire.get());
		}
		if (id == State::stateID::Running)
		{
			if (keystate[SDL_SCANCODE_SPACE])
			{
				m_Commands.push_back(m_Jump.get());
			}
		}
	}

	return m_Commands;
}