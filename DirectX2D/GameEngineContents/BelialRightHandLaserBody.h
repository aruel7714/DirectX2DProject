#pragma once
#include "BelialLaser.h"

// Ό³Έν : 
class BelialRightHandLaserBody : public BelialLaser
{
	friend class BelialRightHand;
public:
	// constrcuter destructer
	BelialRightHandLaserBody();
	~BelialRightHandLaserBody();

	// delete Function
	BelialRightHandLaserBody(const BelialRightHandLaserBody & _Other) = delete;
	BelialRightHandLaserBody(BelialRightHandLaserBody && _Other) noexcept = delete;
	BelialRightHandLaserBody& operator=(const BelialRightHandLaserBody & _Other) = delete;
	BelialRightHandLaserBody& operator=(BelialRightHandLaserBody && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> RightLaserBodyRenderer;

	void ChangeState(LaserState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void EndStart();
	void EndUpdate(float _Delta);
	
};

