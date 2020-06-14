#include "MiniginPCH.h"
#include "PlayerCharacter.h"
#include "C_Movement.h"
#include "C_InputHandling.h"
#include "C_Sprite.h"
#include "C_Collision.h"
#include "C_Fire.h"
#include "C_Player.h"
#include "C_Health.h"
#include "C_Subject.h"
#include "C_Score.h"
#include "O_HealthBar.h"
#include "O_Score.h"

dae::PlayerCharacter::PlayerCharacter(int number)
{
	auto movement = AddComponent<C_Movement>();

	auto inputHandler = AddComponent<C_InputHandling>();

	auto sprite = AddComponent<C_Sprite>();
	sprite->SetTexture("PlayerCharacterSprites.png");
	sprite->SetRect(0.0f, 0.0f, 16.0f, 16.0f);
	//sprite->Scale(0.5f);

	auto collision = AddComponent<C_Collision>();
	
	auto fire = AddComponent<C_Fire>();

	auto player = AddComponent<C_Player>();
	player->SetPlayer(number);

	auto health = AddComponent<C_Health>();
	auto score = AddComponent<C_Score>();

	auto healthObserver = AddComponent<O_HealthBar>();
	auto subject = AddComponent<C_Subject>();
	subject->attach(healthObserver);

	auto scoreObserver = AddComponent<O_Score>();
	subject->attach(scoreObserver);
}
