#pragma once
#include "HandCrossbow.h"

// Ό³Έν : 
class Arrow : public HandCrossbow
{
public:
	// constrcuter destructer
	Arrow();
	~Arrow();

	// delete Function
	Arrow(const Arrow & _Other) = delete;
	Arrow(Arrow && _Other) noexcept = delete;
	Arrow& operator=(const Arrow & _Other) = delete;
	Arrow& operator=(Arrow && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> ArrowRenderer;

	std::shared_ptr<GameEngineCollision> ArrowCollision;

	float4 Dir = float4::ZERO;
	float ArrowSpeed = 1500.0f;
};

