#pragma once
#include "Observer.h"

namespace dae
{
	class O_Test : public Observer
	{
		void Notify(EVENT event) override;
	};
}

