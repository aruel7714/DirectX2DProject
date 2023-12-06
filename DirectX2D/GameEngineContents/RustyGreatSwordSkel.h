#pragma once
#include "Monster.h"

enum class RustyGreatSwordSkelState
{
	Idle,
	Move,
	AttackReady,
	Attack,
	Death,
	Max
};

enum class RustyGreatSwordState
{
	Idle,
	AttackReady,
	Attack,
	Max
};

enum class RustyGreatSwordSkelDir
{
	Left,
	Right
};

// Ό³Έν : 
class RustyGreatSwordSkel : public Monster
{
public:
	// constrcuter destructer
	RustyGreatSwordSkel();
	~RustyGreatSwordSkel();

	// delete Function
	RustyGreatSwordSkel(const RustyGreatSwordSkel & _Other) = delete;
	RustyGreatSwordSkel(RustyGreatSwordSkel && _Other) noexcept = delete;
	RustyGreatSwordSkel& operator=(const RustyGreatSwordSkel & _Other) = delete;
	RustyGreatSwordSkel& operator=(RustyGreatSwordSkel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> RustyGreatSwordSkelRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> RustyGreatSwordRenderer;

	RustyGreatSwordSkelState SkelState = RustyGreatSwordSkelState::Max;
	RustyGreatSwordState SwordState = RustyGreatSwordState::Max;
	RustyGreatSwordSkelDir SkelDir = RustyGreatSwordSkelDir::Left;

	std::shared_ptr<GameEngineCollision> SkelCollision;
	std::shared_ptr<GameEngineCollision> AttackCollision;

	std::shared_ptr<class MonsterLife> RustyGreatSwordSkelLife;

	float AttackReadyTime = 0.0f;

	GameEngineSoundPlayer SkelSound;

	void ChangeSkelState(RustyGreatSwordSkelState _State);
	void SkelStateUpdate(float _Delta);
	void ChangeSkelAnimationState(const std::string& _State);

	void ChangeSwordState(RustyGreatSwordState _State);
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

	void SkelDeathStart();
	void SkelDeathUpdate(float _Delta);

	void SwordIdleStart();
	void SwordIdleUpdate(float _Delta);

	void SwordAttackReadyStart();
	void SwordAttackReadyUpdate(float _Delta);
	
	void SwordAttackStart();
	void SwordAttackUpdate(float _Delta);

	void DirCheck();
};

