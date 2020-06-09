#pragma once
#include <iostream>
#include "GameObject.h"
#include "C_Movement.h"

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
		}
	};

	class MoveLeftCommand : public Command
	{
	public:
		void Execute(GameObject* object) override
		{
			object->GetComponent<C_Movement>()->Move(-1.0f);
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