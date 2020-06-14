#pragma once
#include "GameObject.h"

namespace dae
{
	class Collectable : public GameObject
	{
	public:
		Collectable(int number, float posX, float posY);
	};
}