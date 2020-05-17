#include "MiniginPCH.h"
#include "O_Test.h"

void dae::O_Test::Notify(EVENT event)
{
	std::cout << int(event) << "Works";
}
