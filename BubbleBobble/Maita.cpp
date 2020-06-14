#include "MiniginPCH.h"
#include "Maita.h"
#include "C_Movement.h"
#include "C_Sprite.h"
#include "C_MaitaBehaviour.h"
#include "C_EnemyCollision.h"
#include "C_Fire.h"
#include "C_BubbleBehaviour.h"

dae::Maita::Maita()
{
	auto movement = AddComponent<C_Movement>();

	auto sprite = AddComponent<C_Sprite>();
	sprite->SetTexture("EnemyCharacterSprites.png");
	sprite->SetRect(0.0f, 32.0f, 16.0f, 16.0f);
	//sprite->Scale(0.5f);

	auto behaviour = AddComponent<C_MaitaBehaviour>();

	auto collision = AddComponent<C_EnemyCollision>();

	auto fire = AddComponent<C_Fire>();

	auto bubble = AddComponent<C_BubbleBehaviour>();
}
