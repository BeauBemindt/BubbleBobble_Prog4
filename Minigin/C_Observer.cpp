#include "MiniginPCH.h"
#include "C_Observer.h"
#include "C_Subject.h"
#include "GameObject.h"

dae::C_Observer::C_Observer(GameObject* owner)
	: Component(owner)
	, m_Notified{true}
	, m_Event{}
{
}

void dae::C_Observer::Update()
{
}

void dae::C_Observer::Render() const
{
}

void dae::C_Observer::Notify(EVENT event)
{
	m_Notified = true;
	m_Event = event;
}
