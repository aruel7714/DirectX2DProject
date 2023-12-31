#pragma once
#include "Monster.h"

enum class BigWhiteSkelState
{
	Idle,
	Move,
	Attack,
	AttackReady,
	Death,
	Max
};

enum class BigWhiteSkelDir
{
	Left,
	Right
};

// ���� : 
class BigWhiteSkel : public Monster
{
public:
	// constrcuter destructer
	BigWhiteSkel();
	~BigWhiteSkel();

	// delete Function
	BigWhiteSkel(const BigWhiteSkel & _Other) = delete;
	BigWhiteSkel(BigWhiteSkel && _Other) noexcept = delete;
	BigWhiteSkel& operator=(const BigWhiteSkel & _Other) = delete;
	BigWhiteSkel& operator=(BigWhiteSkel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BigWhiteSkelRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> HpRenderer;

	BigWhiteSkelState State = BigWhiteSkelState::Max;
	BigWhiteSkelDir Dir = BigWhiteSkelDir::Left;

	std::shared_ptr<GameEngineCollision> SkelCollision;
	std::shared_ptr<GameEngineCollision> AttackCollision;

	std::shared_ptr<class MonsterLife> BigWhiteSkelLife;

	float MoveToAttackTime = 0.0f;
	float AttackReadyTime = 0.0f;

	GameEngineSoundPlayer SkelSound;

	void ChangeState(BigWhiteSkelState _State);
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

	void DeathStart();
	void DeathUpdate(float _Delta);

	void DirCheck();
};

