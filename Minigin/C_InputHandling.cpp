#include "MiniginPCH.h"
#include "C_InputHandling.h"
#include "Command.h"
#include "PlayerState.h"

dae::C_InputHandling::C_InputHandling(GameObject* owner)
	: Component(owner)
	, m_Commands{}
	, m_spState{}
{
	m_spState = std::make_shared<FallingState>();
	m_spState->m_ID = State::stateID::Falling;
}

void dae::C_InputHandling::Update()
{
	m_spState->HandleInput(m_spOwner);
	m_spState->Update(m_spOwner);
}

void dae::C_InputHandling::Render() const
{
}

std::shared_ptr<dae::PlayerState> dae::C_InputHandling::GetState()
{
	return m_spState;
}

void dae::C_InputHandling::SetState(PlayerState* state)
{
	m_spState = std::shared_ptr<PlayerState>(state);
}
