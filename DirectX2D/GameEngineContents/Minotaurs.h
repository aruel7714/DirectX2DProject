#pragma once
#include "Monster.h"

enum class MinotaursState
{
	Idle,
	Charge,
	Rush,
	AttackReady,
	Attack,
	Death,
	Stay,
	Max,
};

enum class MinotaursDir
{
	Left,
	Right,
};

// Ό³Έν : 
class Minotaurs : public Monster
{
public:
	// constrcuter destructer
	Minotaurs();
	~Minotaurs();

	// delete Function
	Minotaurs(const Minotaurs & _Other) = delete;
	Minotaurs(Minotaurs && _Other) noexcept = delete;
	Minotaurs& operator=(const Minotaurs & _Other) = delete;
	Minotaurs& operator=(Minotaurs && _Other) noexcept = delete;

	void ChangeStateIdle()
	{
		ChangeState(MinotaursState::Idle);
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> MinotaursRenderer;

	MinotaursState State = MinotaursState::Max;
	MinotaursDir Dir = MinotaursDir::Left;

	std::shared_ptr<GameEngineCollision> MinotaursCollision;
	std::shared_ptr<GameEngineCollision> RushCollision;
	std::shared_ptr<GameEngineCollision> AttackCollision;

	float ChargeTime = 0.0f;
	float RushTime = 0.0f;
	float IdleToAttackTime = 0.0f;
	float AttackReadyTime = 0.0f;

	float4 RushDir = float4::ZERO;
	float RushSpeed = 1000.0f;

	void ChangeState(MinotaursState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void ChargeStart();
	void ChargeUpdate(float _Delta);

	void RushStart();
	void RushUpdate(float _Delta);

	void AttackReadyStart();
	void AttackReadyUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void StayStart();
	void StayUpdate(float _Delta);

	void DirCheck();
};

