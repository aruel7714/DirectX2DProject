#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BelialLeftLaser : public GameEngineActor
{
	friend class BelialLeftHand;
public:
	// constrcuter destructer
	BelialLeftLaser();
	~BelialLeftLaser();

	// delete Function
	BelialLeftLaser(const BelialLeftLaser & _Other) = delete;
	BelialLeftLaser(BelialLeftLaser && _Other) noexcept = delete;
	BelialLeftLaser& operator=(const BelialLeftLaser & _Other) = delete;
	BelialLeftLaser& operator=(BelialLeftLaser && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

