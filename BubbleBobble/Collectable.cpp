#include "MiniginPCH.h"
#include "Collectable.h"
#include "C_Movement.h"
#include "C_Sprite.h"
#include "C_Collectable.h"
#include "GameObject.h"

dae::Collectable::Collectable(int number, float posX, float posY)
{
	SetPosition(posX, posY);
	auto movement = AddComponent<C_Movement>();
	movement->Fall(0.5f);

	auto sprite = AddComponent<C_Sprite>();
	sprite->SetTexture("Collectables.png");
	sprite->SetRect(-16.0f + 16 * number, 0.0f, 16.0f, 16.0f);
	//sprite->Scale(0.5f);
	sprite->Pause();

	auto collectable = AddComponent<C_Collectable>();
	collectable->SetPoints(100 * number);
}