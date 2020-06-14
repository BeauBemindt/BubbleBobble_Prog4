#include "MiniginPCH.h"
#include "Block.h"
#include "C_Sprite.h"

dae::Block::Block()
{
	auto sprite = AddComponent<C_Sprite>();
	sprite->SetTexture("Block.png");
	sprite->SetRect(0.0f, 0.0f, 170.0f, 160.0f);
	//sprite->Scale(0.5f);
	sprite->Pause();
}
