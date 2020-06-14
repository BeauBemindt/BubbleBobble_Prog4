#pragma once
#include "C_Observer.h"
#include "TextObject.h"
#include "Texture2D.h"

namespace dae
{
	class O_Score : public C_Observer
	{
	public:
		O_Score(GameObject* owner);
		void Notify(EVENT event) override;
		void Update() override;
		void Render() const override;
	private:
		std::shared_ptr<TextObject> m_spText;
	};
}

