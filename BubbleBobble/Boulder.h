#pragma once
#include "GameObject.h"

namespace dae
{
	class Boulder : public GameObject
	{
	public:
		Boulder(float startPosX, float startPosY, GameObject* owner, float movementDir);
	private:
		GameObject* m_spPlayer;
	};
}
