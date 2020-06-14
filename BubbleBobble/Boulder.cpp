#include "MiniginPCH.h"
#include "Boulder.h"
#include "C_Sprite.h"
#include "C_Movement.h"
#include "C_Boulder.h"

dae::Boulder::Boulder(float startPosX, float startPosY, GameObject* owner, float movementDir)
	: m_spPlayer{ owner }
{
	SetPosition(startPosX, startPosY);

	auto sprite = AddComponent<C_Sprite>();
	sprite->SetTexture("Boulder.png");
	sprite->SetRect(0.0f, 0.0f, 16.0f, 16.0f);
	sprite->Scale(0.75f);
	//sprite->Pause();

	auto movement = AddComponent<C_Movement>();
	movement->Move(movementDir);
	movement->Fall(0.0f);

	auto boulder = AddComponent<C_Boulder>();
}