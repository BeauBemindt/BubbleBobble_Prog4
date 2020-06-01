#include "MiniginPCH.h"
#include "GameObject.h"
#include "Component.h"

dae::Component::Component(GameObject* owner)
	: m_spOwner{owner}
{
}
