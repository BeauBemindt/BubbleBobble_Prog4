#include "MiniginPCH.h"
#include "C_Text.h"
#include "ResourceManager.h"
#include "GameObject.h"

dae::C_Text::C_Text(GameObject* owner)
	: Component(owner)
	, m_spFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) }
	, m_Text{"Hello World"}
	, m_spTextObject{ std::make_shared<dae::TextObject>(m_Text, m_spFont) }
{
}

void dae::C_Text::Update()
{
}

void dae::C_Text::Render() const
{
	m_spTextObject->Render();
}

void dae::C_Text::SetFont(std::shared_ptr<dae::Font> font)
{
	m_spFont = font;
	m_spTextObject = std::make_shared<dae::TextObject>(m_Text, m_spFont);
}

void dae::C_Text::SetText(std::string text)
{
	m_Text = text;
	m_spTextObject = std::make_shared<dae::TextObject>(m_Text, m_spFont);
}
