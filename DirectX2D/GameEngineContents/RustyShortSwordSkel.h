#pragma once
#include "PlayActor.h"

enum class RustyShortSwordSkelState
{
	Idle,
	Move,
	AttackReady,
	Attack,
	Max,
};

enum class RustyShortSwordState
{
	Idle,
	AttackReady,
	Attack,
	Max,
};

enum class RustyShortSwordSkelDir
{
	Left,
	Right
};

// Ό³Έν : 
class RustyShortSwordSkel : public PlayActor
{
public:
	// constrcuter destructer
	RustyShortSwordSkel();
	~RustyShortSwordSkel();

	// delete Function
	RustyShortSwordSkel(const RustyShortSwordSkel & _Other) = delete;
	RustyShortSwordSkel(RustyShortSwordSkel && _Other) noexcept = delete;
	RustyShortSwordSkel& operator=(const RustyShortSwordSkel & _Other) = delete;
	RustyShortSwordSkel& operator=(RustyShortSwordSkel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> RustyShortSwordSkelRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> RustyShortSwordRenderer;

	RustyShortSwordSkelState SkelState = RustyShortSwordSkelState::Max;
	RustyShortSwordState SwordState = RustyShortSwordState::Max;
	RustyShortSwordSkelDir SkelDir = RustyShortSwordSkelDir::Left;

	std::shared_ptr<GameEngineCollision> SkelCollision;
	std::shared_ptr<GameEngineCollision> AttackCollision;

	float AttackReadyTime = 0.0f;
	float MoveSpeed = 300.0f;

	float SkelHp = 37.0f;

	void ChangeSkelState(RustyShortSwordSkelState _State);
	void SkelStateUpdate(float _Delta);
	void ChangeSkelAnimationState(const std::string& _State);

	void ChangeSwordState(RustyShortSwordState _State);
	void SwordStateUpdate(float _Delta);
	void ChangeSwordAnimationState(const std::string& _State);

	void SkelIdleStart();
	void SkelIdleUpdate(float _Delta);

	void SkelMoveStart();
	void SkelMoveUpdate(float _Delta);

	void SkelAttackReadyStart();
	void SkelAttackReadyUpdate(float _Delta);

	void SkelAttackStart();
	void SkelAttackUpdate(float _Delta);

	void SwordIdleStart();
	void SwordIdleUpdate(float _Delta);

	void SwordAttackReadyStart();
	void SwordAttackReadyUpdate(float _Delta);

	void SwordAttackStart();
	void SwordAttackUpdate(float _Delta);

	void DirCheck();
};

