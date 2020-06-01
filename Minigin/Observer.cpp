#include "MiniginPCH.h"
#include "Observer.h"

dae::Observer::Observer(GameObject* owner)
	: Component(owner)
	, m_spSubject{ std::make_shared<Subject>() }
{
}
