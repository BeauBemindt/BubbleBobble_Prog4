#pragma once
namespace dae
{
	class PlayerState
	{
	public:
		virtual void Update() = 0;
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual void HandleInput() = 0;
	};

	//class JumpingState : public PlayerState
	//{
	//	void Update() override;
	//	void OnEnter() override;
	//	void OnExit() override;
	//	void HandleInput() override;
	//};
}

