#pragma once
#include "C_Observer.h"
#include "TextObject.h"
#include "Texture2D.h"

namespace dae
{
	class O_HealthBar : public C_Observer
	{
	public:
		O_HealthBar(GameObject* owner);
		void Notify(EVENT event) override;
		void Update() override;
		void Render() const override;
	private:
		std::vector<std::shared_ptr<Texture2D>> m_Textures;
	};
}

