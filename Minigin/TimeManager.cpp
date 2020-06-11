#include "MiniginPCH.h"
#include "TimeManager.h"

void dae::TimeManager::Update()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
	if (m_Timing && m_DeltaTime < 1.0f)
	{
		m_Time += m_DeltaTime;
	}
	m_LastTime = currentTime;
}

float dae::TimeManager::GetDeltaTime()
{
	if(m_DeltaTime < 1.0f)
		return m_DeltaTime;
	
	return 0.0f;
}

void dae::TimeManager::StartTiming()
{
	m_Timing = true;
}

void dae::TimeManager::StopTimimg()
{
	m_Timing = false;
	m_Time = 0.0f;
}

float dae::TimeManager::GetTime()
{
	return m_Time;
}
