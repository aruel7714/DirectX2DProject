#include "PlayActor.h"
#pragma once

enum class SkelDogState
{
	Idle,
	Move,
	AttackReady,
	Attack,
};

// Ό³Έν : 
class SkelDog : public PlayActor
{
public:
	// constrcuter destructer
	SkelDog();
	~SkelDog();

	// delete Function
	SkelDog(const SkelDog & _Other) = delete;
	SkelDog(SkelDog && _Other) noexcept = delete;
	SkelDog& operator=(const SkelDog & _Other) = delete;
	SkelDog& operator=(SkelDog && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> SkelDogRenderer;
};

