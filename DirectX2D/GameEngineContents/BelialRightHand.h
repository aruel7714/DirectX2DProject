#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class RightHandState
{
	Idle,
	AttackReady,
	Attack,
	Max,
};

// Ό³Έν : 
class BelialRightHand : public GameEngineActor
{
	friend class Belial;
public:
	// constrcuter destructer
	BelialRightHand();
	~BelialRightHand();

	// delete Function
	BelialRightHand(const BelialRightHand & _Other) = delete;
	BelialRightHand(BelialRightHand && _Other) noexcept = delete;
	BelialRightHand& operator=(const BelialRightHand & _Other) = delete;
	BelialRightHand& operator=(BelialRightHand && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> RightHandRenderer;

	RightHandState State = RightHandState::Max;

	void ChangeState(RightHandState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void AttackReadyStart();
	void AttackReadyUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);
};

