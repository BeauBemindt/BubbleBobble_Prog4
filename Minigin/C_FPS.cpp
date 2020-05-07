#include "MiniginPCH.h"
#include "C_FPS.h"
#include "GameObject.h"
#include <string>
#include "TextObject.h"
#include "ResourceManager.h"

dae::C_FPS::C_FPS(GameObject* owner)
	: Component(owner)
	, m_FPS{}
	, m_LastTime{ std::chrono::high_resolution_clock::now() }
	, m_spText{}
	, m_ChangeCounter{1.0f}
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	m_spText = std::make_shared<TextObject>("0", font);
}

void dae::C_FPS::Update()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	float deltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
	m_LastTime = currentTime;
	m_ChangeCounter += deltaTime;
	if (m_ChangeCounter >= 1.0f)
	{
		m_FPS = int(1.00f / deltaTime);
		m_spText->SetText(std::to_string(m_FPS) + "FPS");
		m_spText->Update();

		m_ChangeCounter = 0.0f;
	}

	m_spText->SetPosition(m_pOwner->m_Transform.GetPosition().x, m_pOwner->m_Transform.GetPosition().y);
}

void dae::C_FPS::Render() const
{
	m_spText->Render();
}