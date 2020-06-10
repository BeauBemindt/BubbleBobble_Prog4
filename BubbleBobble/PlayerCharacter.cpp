#include "MiniginPCH.h"
#include "PlayerCharacter.h"
#include "C_Movement.h"
#include "C_InputHandling.h"
#include "C_Sprite.h"

dae::PlayerCharacter::PlayerCharacter()
{
	SetPosition(216, 0);
	auto movement = AddComponent<C_Movement>();
	auto inputHandler = AddComponent<C_InputHandling>();
	auto sprite = AddComponent<C_Sprite>();
	sprite->SetTexture("Sprites0.png");
	sprite->SetRect(0.0f, 0.0f, 16.0f, 16.0f);
	sprite->Scale(0.5f);
}
