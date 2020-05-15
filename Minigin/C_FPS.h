#pragma once 
#include "Component.h"
#include <chrono>
#include "TextObject.h"

namespace dae
{
	class C_FPS : public Component
	{
	public:
		C_FPS(GameObject* owner);
		void Update() override;
		void Render() const override = 0;
	
		~C_FPS() = default;
		C_FPS(const C_FPS & other) = delete;
		C_FPS(C_FPS && other) = delete;
		C_FPS& operator=(const C_FPS & other) = delete;
		C_FPS& operator=(C_FPS && other) = delete;

		std::shared_ptr<TextObject> m_spText;
	private:
		int m_FPS;
		std::chrono::high_resolution_clock::time_point m_LastTime;
		float m_ChangeCounter;
	};
}


