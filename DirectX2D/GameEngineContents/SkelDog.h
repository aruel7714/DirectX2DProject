#include "PlayActor.h"
#pragma once

enum class SkelDogState
{
	Idle,
	Move,
	AttackReady,
	Attack,
	Max
};

enum class SkelDogDir
{
	Left,
	Right
};

// Ό³Έν : 
class SkelDog : public PlayActor
{
public:
	// constrcuter destructer
	SkelDog();
	~SkelDog();

	// delete Function
	SkelDog(const SkelDog & _Other) = delete;
	SkelDog(SkelDog && _Other) noexcept = delete;
	SkelDog& operator=(const SkelDog & _Other) = delete;
	SkelDog& operator=(SkelDog && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> SkelDogRenderer;

	SkelDogState State = SkelDogState::Max;
	SkelDogDir Dir = SkelDogDir::Left;

	std::shared_ptr<GameEngineCollision> SkelDogCollision;
	std::shared_ptr<GameEngineCollision> SkelDogAttackCollision;

	float MoveSpeed = 300.0f;
	float MoveToAttackTime = 0.0f;
	
	float SkelDogHp = 20.0f;

	void ChangeState(SkelDogState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void AttackReadyStart();
	void AttackReadyUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DirCheck();
};

