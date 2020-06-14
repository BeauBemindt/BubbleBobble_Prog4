#pragma once
#include <iostream>
#include "GameObject.h"
#include "C_Movement.h"
#include "C_Sprite.h"
#include "C_InputHandling.h"
#include "PlayerState.h"
#include "C_Fire.h"
#include "C_Player.h"

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
		void Execute(GameObject* object) override
		{
			auto sprite = object->GetComponent<C_Sprite>();
			float y{};
			if (sprite->GetRect().y % 32 == 0.0f)
			{
				if (object->GetComponent<C_Player>()->GetNumber() == 2)
				{
					y = 96.0f;
				}
				else
				{
					y = 32.0f;
				}
			}
			else
			{
				if (object->GetComponent<C_Player>()->GetNumber() == 2)
				{
					y = 112.0f;
				}
				else
				{
					y = 48.0f;
				}
			}
			sprite->SetRect(float(sprite->GetRect().x), y, float(sprite->GetRect().w), float(sprite->GetRect().h));
			if (int(y) % 32 == 0.0f)
			{
				object->GetComponent<C_Fire>()->Fire(1.0f);
			}
			else
			{
				object->GetComponent<C_Fire>()->Fire(-1.0f);
			}
		};
	};

	class MoveRightCommand : public Command
	{
	public:
		void Execute(GameObject* object) override
		{
			object->GetComponent<C_Movement>()->Move(1.0f);
			auto sprite = object->GetComponent<C_Sprite>();
			if (object->GetComponent<C_Player>()->GetNumber() == 1)
			{
				sprite->SetRect(float(sprite->GetRect().x), 0.0f, float(sprite->GetRect().w), float(sprite->GetRect().h));
			}
			else
			{
				sprite->SetRect(float(sprite->GetRect().x), 64.0f, float(sprite->GetRect().w), float(sprite->GetRect().h));
			}
		}
	};

	class MoveLeftCommand : public Command
	{
	public:
		void Execute(GameObject* object) override
		{
			object->GetComponent<C_Movement>()->Move(-1.0f);
			auto sprite = object->GetComponent<C_Sprite>();
			if (object->GetComponent<C_Player>()->GetNumber() == 1)
			{
				sprite->SetRect(float(sprite->GetRect().x), 16.0f, float(sprite->GetRect().w), float(sprite->GetRect().h));
			}
			else
			{
				sprite->SetRect(float(sprite->GetRect().x), 80.0f, float(sprite->GetRect().w), float(sprite->GetRect().h));
			}
		}
	};

	class StandStillCommand : public Command
	{
	public:
		void Execute(GameObject* object) override
		{
			object->GetComponent<C_Movement>()->Move(0.0f);
			object->GetComponent<C_Sprite>()->Pause();
		}
	};

	class JumpCommand : public Command
	{
	public:
		void Execute(GameObject* object) override
		{
			object->GetComponent<C_InputHandling>()->GetState()->OnExit(object);
			object->GetComponent<C_InputHandling>()->SetState(new JumpingState());
			object->GetComponent<C_InputHandling>()->GetState()->OnEnter(object);
		}
	};
}