#pragma once
#include "BelialLaser.h"

// Ό³Έν : 
class BelialLeftHandLaserBody : public BelialLaser
{
	friend class BelialLeftHand;
public:
	// constrcuter destructer
	BelialLeftHandLaserBody();
	~BelialLeftHandLaserBody();

	// delete Function
	BelialLeftHandLaserBody(const BelialLeftHandLaserBody & _Other) = delete;
	BelialLeftHandLaserBody(BelialLeftHandLaserBody && _Other) noexcept = delete;
	BelialLeftHandLaserBody& operator=(const BelialLeftHandLaserBody & _Other) = delete;
	BelialLeftHandLaserBody& operator=(BelialLeftHandLaserBody && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> LeftLaserBodyRenderer;

	void ChangeState(LaserState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void EndStart();
	void EndUpdate(float _Delta);
};

