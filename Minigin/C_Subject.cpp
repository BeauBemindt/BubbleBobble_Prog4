#include "MiniginPCH.h"
#include "C_Subject.h"
#include "C_Observer.h"
#include <algorithm>
#include "GameObject.h"

dae::C_Subject::C_Subject(GameObject* owner)
	: Component(owner)
	, m_Observers{}
{
}

void dae::C_Subject::attach(std::shared_ptr<C_Observer> observer)
{
	m_Observers.emplace_back(observer);
	observer->Attach(this);
}

void dae::C_Subject::detach(std::shared_ptr<C_Observer> observer)
{
	m_Observers.remove(observer);
}

void dae::C_Subject::Update()
{
}

void dae::C_Subject::Render() const
{
}

void dae::C_Subject::notify(EVENT event)
{
	if (m_Observers.size() != NULL)
	{
		for (auto const& obs : m_Observers)
		{
			obs->Notify(event);
		}
	}
}
