#include "MiniginPCH.h"
#include "ZenChan.h"
#include "C_Movement.h"
#include "C_Sprite.h"
#include "C_ZenChanBehaviour.h"
#include "C_EnemyCollision.h"
#include "C_BubbleBehaviour.h"

dae::ZenChan::ZenChan()
{
	SetPosition(150, 50);

	auto movement = AddComponent<C_Movement>();

	auto sprite = AddComponent<C_Sprite>();
	sprite->SetTexture("EnemyCharacterSprites.png");
	sprite->SetRect(0.0f, 0.0f, 16.0f, 16.0f);
	//sprite->Scale(0.5f);

	auto behaviour = AddComponent<C_ZenChanBehaviour>();

	auto collision = AddComponent<C_EnemyCollision>();

	auto bubble = AddComponent<C_BubbleBehaviour>();
}