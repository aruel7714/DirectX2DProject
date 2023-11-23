#pragma once
#include "PlayActor.h"

enum class ArcherSkelState
{
	Idle,
	AttackReady,
	Attack,
	Max,
};

enum class SkelBowState
{
	Idle,
	AttackReady,
	Attack,
	Max
};

enum class ArcherSkelDir
{
	Left,
	Right,
};

// Ό³Έν : 
class ArcherSkel : public PlayActor
{
public:
	// constrcuter destructer
	ArcherSkel();
	~ArcherSkel();

	// delete Function
	ArcherSkel(const ArcherSkel & _Other) = delete;
	ArcherSkel(ArcherSkel && _Other) noexcept = delete;
	ArcherSkel& operator=(const ArcherSkel & _Other) = delete;
	ArcherSkel& operator=(ArcherSkel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta);
private:
	std::shared_ptr<GameEngineSpriteRenderer> ArcherSkelRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> BowRenderer;

	ArcherSkelState SkelState = ArcherSkelState::Max;
	SkelBowState BowState = SkelBowState::Max;
	ArcherSkelDir SkelDir = ArcherSkelDir::Left;

	std::shared_ptr<GameEngineCollision> SkelCollision;

	float IdleToAttackTime = 0.0f;
	float AttackTime = 0.0f;

	float4 SavePlayerPos = float4::ZERO;
	float4 SaveDir = float4::ZERO;
	float SaveDeg = 0.0f;

	float ArcherSkelHp = 30.0f;

	void ChangeSkelState(ArcherSkelState _State);
	void SkelStateUpdate(float _Delta);
	void ChangeSkelAnimationState(const std::string& _State);

	void ChangeBowState(SkelBowState _State);
	void BowStateUpdate(float _Delta);
	void ChangeBowAnimationState(const std::string& _State);

	void SkelIdleStart();
	void SkelIdleUpdate(float _Delta);

	void SkelAttackReadyStart();
	void SkelAttackReadyUpdate(float _Delta);

	void SkelAttackStart();
	void SkelAttackUpdate(float _Delta);

	void BowIdleStart();
	void BowIdleUpdate(float _Delta);

	void BowAttackReadyStart();
	void BowAttackReadyUpdate(float _Delta);

	void BowAttackStart();
	void BowAttackUpdate(float _Delta);

	void DirCheck();
};

