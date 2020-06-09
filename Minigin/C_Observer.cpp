#include "MiniginPCH.h"
#include "C_Observer.h"

dae::C_Observer::C_Observer(GameObject* owner)
	: Component(owner)
	, m_spSubject{}
{
}

void dae::C_Observer::Attach(C_Subject* subject)
{
	m_spSubject = subject;
}
