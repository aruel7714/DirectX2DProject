#pragma once
#include "Monster.h"

enum class LittleGhostState
{
	Idle,
	Move,
	Attack,
	Death,
	Max
};

enum class LittleGhostDir
{
	Left,
	Right,
};

// Ό³Έν : 
class LittleGhost : public Monster
{
public:
	// constrcuter destructer
	LittleGhost();
	~LittleGhost();

	// delete Function
	LittleGhost(const LittleGhost & _Other) = delete;
	LittleGhost(LittleGhost && _Other) noexcept = delete;
	LittleGhost& operator=(const LittleGhost & _Other) = delete;
	LittleGhost& operator=(LittleGhost && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delat) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> LittleGhostRenderer;
	
	LittleGhostState State = LittleGhostState::Max;
	LittleGhostDir Dir = LittleGhostDir::Left;

	std::shared_ptr<GameEngineCollision> LittleGhostCollision;

	std::shared_ptr<class MonsterLife> LittleGhostLife;

	float4 SaveDir = float4::ZERO;
	float Distance = 0.0f;

	float MoveToAttackTime = 0.0f;
	float AttackTime = 0.0f;

	GameEngineSoundPlayer GhostSound;

	void ChangeState(LittleGhostState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);
	
	void MoveStart();
	void MoveUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void DirCheck();
};

