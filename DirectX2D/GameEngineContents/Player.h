#pragma once
#include "PlayActor.h"

enum class PlayerState
{
	Idle,
	Run,
	Jump,
	Dash,
	DownJump,
	Stay,
	Ending,
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
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void ChangeStateStay();
	void ChangeStateEnding();
	void ChangeStateIdle();
	bool IsStateStay();

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

	float GetWeaponDamage()
	{
		return WeaponDamage;
	}

	bool GetIsDownValue()
	{
		return IsDown;
	}

	void IsFocusFalse()
	{
		IsFocus = false;
	}

	void IsFocusTrue()
	{
		IsFocus = true;
	}

	void IsDownFalse()
	{
		IsDown = false;
	}

	int GetCurHp()
	{
		return CurHp;
	}

	int GetMaxHp()
	{
		return MaxHp;
	}

	void Damaging(int _Damage)
	{
		CurHp -= _Damage;
	}

	void WeaponOn();
	void WeaponOff();

protected:
	void Start();
	void Update(float _Delta);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainRenderer;

	PlayerState State = PlayerState::Max;

	std::shared_ptr<class HandCrossbow> WeaponHandCrossbow;
	
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

	void EndingStart();
	void EndingUpdate(float _Delta);

	void CameraFocus();

	void DirCheck();

	void DownFloorFunc();

	void LevelStart(GameEngineLevel* _PrevLevel) override;

	void SteleToPlayerMove(float _Delta, float ResultPos);

	void PlayerCollisionEvent(float _Delta);

	

	//void Gravity(float _Delta);
private:
	void StatusUpdate();

	PlayerDir Dir = PlayerDir::Right;

	//float Speed = 1000.0f;
	float Speed = 500.0f;
	
	GameEngineColor Color;

	float4 PlayerScale = float4::ZERO;
	float4 PlayerPosition = float4::ZERO;

	float WeaponDamage = 0.0f;
	int HaveGold = 0;
	int HaveHungry = 0;
	int MaxHp = 80;
	int CurHp = 80;

	float NotDamageTime = 0.0f;

	std::shared_ptr<class PlayerLife> UILife;
	std::shared_ptr<class PlayerEquippedWeapon> UIWeapon;
	std::shared_ptr<class PlayerGold> UIHaveGold;
	std::shared_ptr<class PlayerFood> UIHaveHungry;

	bool IsFocus = true;

	bool IsDown = false;

	GameEngineSoundPlayer PlayerSound;

private:
	//Debug
	float CheckDelta = 0.0f;

	float4 Scale = float4::ZERO;

	std::shared_ptr<GameEngineCollision> PlayerCollision;

	bool IsBlue = true;

};

