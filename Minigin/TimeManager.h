#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class TimeManager : public Singleton<TimeManager>
	{
	public:
		void Update();
		float GetDeltaTime();
	private:
		std::chrono::high_resolution_clock::time_point m_LastTime{};
		float m_DeltaTime{};
		bool m_Timing{};
	};
}

