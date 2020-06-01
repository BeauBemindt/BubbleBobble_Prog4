#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"
#include <algorithm>
#include "GameObject.h"

dae::Subject::Subject()
	: m_Observers{}
{
}

dae::Subject::~Subject()
{
}

void dae::Subject::attach(std::shared_ptr<Observer> observer)
{
	m_Observers.emplace_back(observer);
}

void dae::Subject::detach(std::shared_ptr<Observer> observer)
{
	m_Observers.remove(observer);
}

void dae::Subject::notify(EVENT event)
{
	if (m_Observers.size() != NULL)
	{
		for (auto const& obs : m_Observers)
		{
			obs->Notify(event);
		}
	}
}
