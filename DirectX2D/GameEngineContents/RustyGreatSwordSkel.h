#pragma once
#include "PlayActor.h"

enum class RustyGreatSwordSkelState
{
	Idle,
	Move,
	Attack,
	AttackReady,
	Max
};

enum class RustyGreatSwordState
{
	Idle,
	Attack,
	AttackReady,
	Max
};

enum class RustyGreatSwordSkelDir
{
	Left,
	Right
};

// Ό³Έν : 
class RustyGreatSwordSkel : public PlayActor
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
	RustyGreatSwordSkelDir SkelDir = RustyGreatSwordSkelDir::Right;

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

	void SwordIdleStart();
	void SwordIdleUpdate(float _Delta);

	void SwordAttackReadyStart();
	void SwordAttackReadyUpdate(float _Delta);
	
	void SwordAttackStart();
	void SwordAttackUpdate(float _Delta);
};

