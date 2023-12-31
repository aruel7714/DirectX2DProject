#pragma once
#include "BelialLaser.h"

// ���� : 
class BelialLeftHandLaserHead : public BelialLaser
{
	friend class BelialLeftHand;
public:
	// constrcuter destructer
	BelialLeftHandLaserHead();
	~BelialLeftHandLaserHead();

	// delete Function
	BelialLeftHandLaserHead(const BelialLeftHandLaserHead & _Other) = delete;
	BelialLeftHandLaserHead(BelialLeftHandLaserHead && _Other) noexcept = delete;
	BelialLeftHandLaserHead& operator=(const BelialLeftHandLaserHead & _Other) = delete;
	BelialLeftHandLaserHead& operator=(BelialLeftHandLaserHead && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> LeftLaserHeadRenderer;

	void ChangeState(LaserState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void EndStart();
	void EndUpdate(float _Delta);
};

