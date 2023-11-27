#pragma once
#include "Monster.h"

enum class RedBatState
{
	Move,
	Attack,
	Death,
	Max,
};

enum class RedBatDir
{
	Left,
	Right
};

// Ό³Έν : 
class RedBat : public Monster
{
public:
	// constrcuter destructer
	RedBat();
	~RedBat();

	// delete Function
	RedBat(const RedBat & _Other) = delete;
	RedBat(RedBat && _Other) noexcept = delete;
	RedBat& operator=(const RedBat & _Other) = delete;
	RedBat& operator=(RedBat && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> RedBatRenderer;

	RedBatState State = RedBatState::Max;
	RedBatDir Dir = RedBatDir::Left;

	std::shared_ptr<GameEngineCollision> RedBatCollision;

	GameEngineRandom Random;
	float RandomDir;

	float MoveTime = 0.0f;
	float AttackTime = 0.0f;

	void ChangeState(RedBatState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void DirCheck();
};

