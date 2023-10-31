#pragma once
#include "PlayActor.h"

enum class RustyShortSwordSkelState
{
	Idle,
	Move,
	Attack,
	AttackReady
};

enum class RustyShortSwordState
{
	Attack,
	AttackReady,
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
};

