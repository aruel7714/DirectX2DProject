#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BelialRightLaser : public GameEngineActor
{
	friend class BelialRightHand;
public:
	// constrcuter destructer
	BelialRightLaser();
	~BelialRightLaser();

	// delete Function
	BelialRightLaser(const BelialRightLaser & _Other) = delete;
	BelialRightLaser(BelialRightLaser && _Other) noexcept = delete;
	BelialRightLaser& operator=(const BelialRightLaser & _Other) = delete;
	BelialRightLaser& operator=(BelialRightLaser && _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta);
private:

};

