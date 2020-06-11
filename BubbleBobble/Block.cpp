#include "MiniginPCH.h"
#include "Block.h"
#include "C_Sprite.h"
#include "C_Collision.h"

dae::Block::Block()
{
	SetPosition(150, 300);

	auto sprite = AddComponent<C_Sprite>();
	sprite->SetTexture("Block.png");
	sprite->SetRect(0.0f, 0.0f, 170.0f, 160.0f);
	sprite->Scale(0.5f);

	auto collision = AddComponent<C_Collision>();
}
