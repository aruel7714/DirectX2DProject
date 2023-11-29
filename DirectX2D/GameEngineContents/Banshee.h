#pragma once
#include "Monster.h"

enum class BansheeState
{
	Idle,
	Attack,
	Death,
	Max
};

enum class BansheeDir
{
	Left,
	Right,
};

// Ό³Έν : 
class Banshee : public Monster
{
public:
	// constrcuter destructer
	Banshee();
	~Banshee();

	// delete Function
	Banshee(const Banshee & _Other) = delete;
	Banshee(Banshee && _Other) noexcept = delete;
	Banshee& operator=(const Banshee & _Other) = delete;
	Banshee& operator=(Banshee && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BansheeRenderer;

	BansheeState State = BansheeState::Max;
	BansheeDir Dir = BansheeDir::Left;

	std::shared_ptr<GameEngineCollision> BansheeCollision;

	std::shared_ptr<class MonsterLife> BansheeLife;

	float IdleToAttackTime = 0.0f;

	void ChangeState(BansheeState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void DirCheck();
};

