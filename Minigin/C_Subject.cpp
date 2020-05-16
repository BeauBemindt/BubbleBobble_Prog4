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

void dae::C_Subject::Update()
{
}

void dae::C_Subject::Render() const
{
}

void dae::C_Subject::attach(C_Observer* observer)
{
	m_Observers.emplace_back(observer);
}

void dae::C_Subject::detach(C_Observer* observer)
{
	m_Observers.remove(std::shared_ptr<C_Observer>(observer));
}

void dae::C_Subject::notify()
{
	std::for_each(m_Observers.begin(), m_Observers.end(), [](const std::shared_ptr<C_Observer>& observer)
		{
			observer->Notify(EVENT::a);
		});
}
