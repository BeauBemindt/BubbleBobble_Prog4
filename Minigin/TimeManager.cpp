#include "MiniginPCH.h"
#include "TimeManager.h"

void dae::TimeManager::Update()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
	m_LastTime = currentTime;
}

float dae::TimeManager::GetDeltaTime()
{
	if(m_DeltaTime < 1.0f)
		return m_DeltaTime;
	
	return 0.0f;
}
