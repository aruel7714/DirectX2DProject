#pragma once
#include "PlayActor.h"

enum class RustyGreatSwordSkelState
{
	Idle,
	Move,
	Attack,
	AttackReady
};

enum class RustyGreatSwordState
{
	Attack,
	AttackReady,
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
};

