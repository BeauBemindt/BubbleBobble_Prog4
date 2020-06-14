#include "MiniginPCH.h"
#include "Bubble.h"
#include "C_Sprite.h"
#include "C_Movement.h"
#include "C_Bubble.h"

dae::Bubble::Bubble(float startPosX, float startPosY, GameObject* owner, float movementDir)
	: m_spPlayer{owner}
{
	SetPosition(startPosX, startPosY);

	auto sprite = AddComponent<C_Sprite>();
	sprite->SetTexture("Sprites1.png");
	sprite->SetRect(0.0f, 192.0f, 16.0f, 16.0f);
	sprite->Scale(0.75f);
	//sprite->Pause();

	auto movement = AddComponent<C_Movement>();
	movement->Move(movementDir);
	movement->Fall(0.0f);

	auto bubble = AddComponent<C_Bubble>();
}
