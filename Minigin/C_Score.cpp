#include "MiniginPCH.h"
#include "C_Score.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "C_Subject.h"

dae::C_Score::C_Score(GameObject* owner)
	: Component(owner)
	, m_Score{ 0 }
{
}

void dae::C_Score::Update()
{
}

void dae::C_Score::Render() const
{
}

void dae::C_Score::Add(int amount)
{
	m_Score += amount;

	// notify score bar
	m_spOwner->GetComponent<C_Subject>()->notify(EVENT::collected);
}

int dae::C_Score::GetScore() const
{
	return m_Score;
}