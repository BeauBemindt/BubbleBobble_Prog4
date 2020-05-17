#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"
#include <algorithm>
#include "GameObject.h"

dae::Subject::Subject()
	: m_Observers{}
{
}

void dae::Subject::attach(Observer* observer)
{
	m_Observers.emplace_back(observer);
	observer->Attach(this);
}

void dae::Subject::detach(Observer* observer)
{
	observer->detach();
	m_Observers.remove(std::shared_ptr<Observer>(observer));
}
