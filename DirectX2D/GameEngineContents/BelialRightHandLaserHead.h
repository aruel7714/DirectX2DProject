#pragma once
#include "BelialLaser.h"

// Ό³Έν : 
class BelialRightHandLaserHead : public BelialLaser
{
	friend class BelialRightHand;
public:
	// constrcuter destructer
	BelialRightHandLaserHead();
	~BelialRightHandLaserHead();

	// delete Function
	BelialRightHandLaserHead(const BelialRightHandLaserHead & _Other) = delete;
	BelialRightHandLaserHead(BelialRightHandLaserHead && _Other) noexcept = delete;
	BelialRightHandLaserHead& operator=(const BelialRightHandLaserHead & _Other) = delete;
	BelialRightHandLaserHead& operator=(BelialRightHandLaserHead && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> RightLaserHeadRenderer;

	void ChangeState(LaserState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void EndStart();
	void EndUpdate(float _Delta);
};

