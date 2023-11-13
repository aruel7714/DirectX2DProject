#pragma once
#include "PlayActor.h"

enum class MinotaursState
{
	Idle,
	Charge,
	Rush,
	AttackReady,
	Attack,
	Max,
};

enum class MinotaursDir
{
	Left,
	Right,
};

// Ό³Έν : 
class Minotaurs : public PlayActor
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

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> MinotaursRenderer;

	MinotaursState State = MinotaursState::Max;
	MinotaursDir Dir = MinotaursDir::Left;

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
};

