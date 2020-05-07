#pragma once
#include "Component.h"
#include "TextObject.h"
#include <Memory>

namespace dae
{
	class C_Text : public Component
	{
	public:
		C_Text(GameObject* owner);
		void Update() override;
		void Render() const override;
		void SetFont(std::shared_ptr<dae::Font> font);
		void SetText(std::string text);
	
		~C_Text() = default;
		C_Text(const C_Text & other) = delete;
		C_Text(C_Text && other) = delete;
		C_Text& operator=(const C_Text & other) = delete;
		C_Text& operator=(C_Text && other) = delete;
	private:
		std::shared_ptr<dae::Font> m_spFont;
		std::string m_Text;
		std::shared_ptr<dae::TextObject> m_spTextObject;
	};
}


