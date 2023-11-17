#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class LeftHandState
{
	Idle,
	AttackReady,
	Attack,
	Max,
};

// Ό³Έν : 
class BelialLeftHand : public GameEngineActor
{
	friend class Belial;
public:
	// constrcuter destructer
	BelialLeftHand();
	~BelialLeftHand();

	// delete Function
	BelialLeftHand(const BelialLeftHand & _Other) = delete;
	BelialLeftHand(BelialLeftHand && _Other) noexcept = delete;
	BelialLeftHand& operator=(const BelialLeftHand & _Other) = delete;
	BelialLeftHand& operator=(BelialLeftHand && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> LeftHandRenderer;

	LeftHandState State = LeftHandState::Max;

	void ChangeState(LeftHandState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void AttackReadyStart();
	void AttackReadyUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	float DebugTime = 0.0f;
};

