#pragma once 
#include "Component.h"
#include <chrono>
#include "TextObject.h"
#include "Command.h"

namespace dae
{
	class C_FPS : public Component
	{
	public:
		C_FPS(GameObject* owner);
		void Update() override;
		void Render() const override;

	private:
		int m_FPS;
		std::chrono::high_resolution_clock::time_point m_LastTime;
		float m_ChangeCounter;
		std::shared_ptr<TextObject> m_spText;
	};
}


