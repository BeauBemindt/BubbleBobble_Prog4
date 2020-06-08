#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	//SDL_Event e;
	//while (SDL_PollEvent(&e)) {
	//	if (e.type == SDL_QUIT) {
	//		return false;
	//	}
	//	if (e.type == SDL_KEYDOWN)
	//	{
	//		std::cout << "jep" << std::endl;
	//	}
	//	if (e.type == SDL_MOUSEBUTTONDOWN) {
	//		
	//	}
	//}
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
	default: return false;
	}
}

bool dae::InputManager::IsPressed(KeyboardButton button) const
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (button)
			{
			case KeyboardButton::ButtonSpace:
				return e.key.keysym.sym == SDLK_SPACE;
			case KeyboardButton::ButtonB:
				return e.key.keysym.sym == SDLK_b;
			case KeyboardButton::ButtonX:
				return e.key.keysym.sym == SDLK_x;
			case KeyboardButton::ButtonY:
				return e.key.keysym.sym == SDLK_y;
			}
		}
	}
	return false;
}

Command* dae::InputManager::HandleInput()
{
	if (IsPressed(KeyboardButton::ButtonSpace))
	{
		return m_Fire.get();
	}

	// Nothing pressed, so do nothing.
	return nullptr;
}