#include "MiniginPCH.h"
#include "C_FPS.h"
#include "GameObject.h"
#include <string>
#include "TextObject.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "C_Subject.h"
#include "TimeManager.h"

dae::C_FPS::C_FPS(GameObject* owner)
	: Component(owner)
	, m_FPS{}
	, m_LastTime{ std::chrono::high_resolution_clock::now() }
	, m_spText{}
	, m_ChangeCounter{0.0f}
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	m_spText = std::make_shared<TextObject>("0", font, SDL_Color{255, 255, 0});
}

void dae::C_FPS::Update()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	m_LastTime = currentTime;
	m_ChangeCounter += TimeManager::GetInstance().GetDeltaTime();
	if (m_ChangeCounter >=1.0f)
	{
		m_FPS = int(1.00f / TimeManager::GetInstance().GetDeltaTime());
		m_spText->SetText(std::to_string(m_FPS) + "FPS");
		m_spText->Update();

		m_ChangeCounter = 0.0f;

	}

	m_spText->SetPosition(m_spOwner->m_Transform.GetPosition().x, m_spOwner->m_Transform.GetPosition().y);

	if (InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonA))
	{
		m_spOwner->GetComponent<C_Subject>()->notify(EVENT::a);
	}
	//HandleInput();
}

void dae::C_FPS::Render() const
{
	m_spText->Render();
}
