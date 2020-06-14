#pragma once
#include "Component.h"
#include "TextObject.h"
#include "Texture2D.h"

namespace dae
{
	class C_StartScreen : public Component
	{
	public:
		C_StartScreen(GameObject* owner);
		void Update() override;
		void Render() const override;
	private:
		std::shared_ptr<TextObject> m_spText;
		std::shared_ptr<Texture2D> m_spTextureButtonY;
		std::shared_ptr<Texture2D> m_spTextureButtonB;
		std::shared_ptr<Texture2D> m_spBackground;
	};
}

