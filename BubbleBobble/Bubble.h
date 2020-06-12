#pragma once
#include "GameObject.h"

namespace dae
{
	class Bubble : public GameObject
	{
	public:
		Bubble(float startPosX, float startPosY, GameObject* owner, float movementDir);
	private:
		GameObject* m_spPlayer;
	};
}

