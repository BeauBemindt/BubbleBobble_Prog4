#include "MiniginPCH.h"
#include "Observer.h"

void dae::Observer::Attach(Subject* subject)
{
	m_pSubject = subject;
}

void dae::Observer::detach()
{
	m_pSubject = nullptr;
}
