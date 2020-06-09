#include "MiniginPCH.h"
#include "O_Test.h"

dae::O_Test::O_Test(GameObject* owner)
	: C_Observer(owner)
{
}

void dae::O_Test::Notify(EVENT event)
{
	std::cout << int(event) << "Works";
}

void dae::O_Test::Update()
{
}

void dae::O_Test::Render() const
{
}
