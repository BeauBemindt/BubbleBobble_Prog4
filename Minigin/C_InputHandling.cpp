#include "MiniginPCH.h"
#include "C_InputHandling.h"
#include "Command.h"
#include "PlayerState.h"

dae::RunningState dae::PlayerState::m_RunningState{};
dae::JumpingState dae::PlayerState::m_JumpingState{};

dae::C_InputHandling::C_InputHandling(GameObject* owner)
	: Component(owner)
	, m_Commands{}
	, m_pState{ &PlayerState::m_RunningState }
{
}

void dae::C_InputHandling::Update()
{
	m_pState->Update();
	m_pState->HandleInput(m_spOwner);
}

void dae::C_InputHandling::Render() const
{
}

dae::PlayerState* dae::C_InputHandling::GetState() const
{
	return m_pState;
}
