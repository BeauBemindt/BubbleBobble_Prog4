#pragma once
namespace dae
{
	class State
	{
	public:
		virtual void Update() = 0;
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual State* HandleInput() = 0;
	};
}

