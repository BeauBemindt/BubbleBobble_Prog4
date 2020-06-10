#pragma once
#include <iostream>
#include "GameObject.h"
#include "C_Movement.h"
#include "C_Sprite.h"

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(GameObject* object) = 0;
	};

	class FireCommand : public Command
	{
	public:
		void Execute(GameObject*) override
		{
			std::cout << "yes" << std::endl;
		};
	};

	class MoveRightCommand : public Command
	{
	public:
		void Execute(GameObject* object) override
		{
			object->GetComponent<C_Movement>()->Move(1.0f);
			auto sprite = object->GetComponent<C_Sprite>();
			float x = float(sprite->GetRect().x + 34);
			if (x > 256)
			{
				x = 0;
			}
			sprite->SetRect(x, 0.0f, float(sprite->GetRect().w), float(sprite->GetRect().h));
		}
	};

	class MoveLeftCommand : public Command
	{
	public:
		void Execute(GameObject* object) override
		{
			object->GetComponent<C_Movement>()->Move(-1.0f);
			auto sprite = object->GetComponent<C_Sprite>();
			float x = float(sprite->GetRect().x + 34);
			if (x > 256)
			{
				x = 0;
			}
			sprite->SetRect(x, 16.0f, float(sprite->GetRect().w), float(sprite->GetRect().h));
		}
	};

	class JumpCommand : public Command
	{
	public:
		void Execute(GameObject* object) override
		{
			object->GetComponent<C_Movement>()->Jump();
		}
	};
}