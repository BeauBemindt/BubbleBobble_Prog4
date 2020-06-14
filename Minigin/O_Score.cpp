#include "MiniginPCH.h"
#include "O_Score.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "C_Score.h"
#include "C_Player.h"

dae::O_Score::O_Score(GameObject* owner)
	: C_Observer(owner)
	, m_spText{}
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);
	m_spText = std::make_shared<TextObject>("Score: 0", font, SDL_Color{ 255, 255, 0 });
	m_spText->SetPosition((m_spOwner->GetComponent<C_Player>()->GetNumber() - 1) * 470.0f + 16.0f, 48.0f);
}

void dae::O_Score::Notify(EVENT event)
{
	if (event == EVENT::collected)
	{
		std::string text{"Score: "};
		text += std::to_string(m_spOwner->GetComponent<C_Score>()->GetScore());
		m_spText->SetText(text);
	}
}

void dae::O_Score::Update()
{
	m_spText->Update();
}

void dae::O_Score::Render() const
{
	m_spText->Render();
}