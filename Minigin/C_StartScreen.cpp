#include "MiniginPCH.h"
#include "C_StartScreen.h"
#include "LevelManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::C_StartScreen::C_StartScreen(GameObject* owner)
	: Component(owner)
	, m_spText{}
	, m_spTextureButtonB{}
	, m_spTextureButtonY{}
	, m_spBackground{}
{
	m_spTextureButtonB = ResourceManager::GetInstance().LoadTexture("ButtonB.png");
	m_spTextureButtonY = ResourceManager::GetInstance().LoadTexture("ButtonY.png");
	m_spBackground = ResourceManager::GetInstance().LoadTexture("Background.png");

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 48);
	m_spText = std::make_shared<TextObject>("SOLO              CO-OP", font, SDL_Color{ 255, 255, 0 });
	m_spText->SetPosition(100.0f, 475.0f);
}

void dae::C_StartScreen::Update()
{
	m_spText->Update();
}

void dae::C_StartScreen::Render() const
{
	if (!LevelManager::GetInstance().IsInGame())
	{
		Renderer::GetInstance().RenderTexture(*m_spBackground, 0.0f, 0.0f);
		Renderer::GetInstance().RenderTexture(*m_spTextureButtonB, 415.0f, 400.0f, 75.0f, 75.0f);
		Renderer::GetInstance().RenderTexture(*m_spTextureButtonY, 125.0f, 400.0f, 75.0f, 75.0f);
		m_spText->Render();
	}
}
