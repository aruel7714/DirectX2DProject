#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "PlayActor.h"

enum class PlayerState
{
	Idle,
	Run,
	Jump,
	Dash,
	DownJump,
	Stay,
	Max
};

enum class PlayerDir
{
	Left,
	Right,
};

// Ό³Έν : 
class Player : public PlayActor
{
public:
	static Player* MainPlayer;
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player & _Other) = delete;
	Player(Player && _Other) noexcept = delete;
	Player& operator=(const Player & _Other) = delete;
	Player& operator=(Player && _Other) noexcept = delete;

	void ChangeStateStay();

	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}

	float4 GetRendererScale()
	{
		return MainRenderer->GetImageTransform().GetLocalScale();
	}

	PlayerDir GetPlayerDir()
	{
		return Dir;
	}

protected:
	void Start();
	void Update(float _Delta);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainRenderer;

	PlayerState State = PlayerState::Max;
	
	void ChangeState(PlayerState _State);
	void StateUpdate(float _Delta);

	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

	void DashStart();
	void DashUpdate(float _Delta);

	void DownJumpStart();
	void DownJumpUpdate(float _Delta);
	
	void StayStart();
	void StayUpdate(float _Delta);

	void CameraFocus();

	void DirCheck();

	void DownFloorFunc();

	void LevelStart(GameEngineLevel* _PrevLevel) override;

	//void Gravity(float _Delta);
private:
	void StatusUpdate();

	PlayerDir Dir = PlayerDir::Right;

	//float Speed = 1000.0f;
	float Speed = 500.0f;
	
	GameEngineColor Color;

	float4 PlayerScale = float4::ZERO;
	float4 PlayerPosition = float4::ZERO;

private:
	//Debug
	float CheckDelta = 0.0f;

	float4 Scale = float4::ZERO;

	std::shared_ptr<GameEngineCollision> PlayerCollision;

	bool IsBlue = true;

};

