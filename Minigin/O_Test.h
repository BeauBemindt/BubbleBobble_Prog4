#pragma once
#include "C_Observer.h"

namespace dae
{
	class O_Test : public C_Observer
	{
	public:
		O_Test(GameObject* owner);
		void Notify(EVENT event) override;
		void Update() override;
		void Render() const override;
	};
}

