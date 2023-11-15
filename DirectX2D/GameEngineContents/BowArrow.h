#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BowArrow : public GameEngineActor
{
	friend class ArcherSkel;
public:
	// constrcuter destructer
	BowArrow();
	~BowArrow();

	// delete Function
	BowArrow(const BowArrow & _Other) = delete;
	BowArrow(BowArrow && _Other) noexcept = delete;
	BowArrow& operator=(const BowArrow & _Other) = delete;
	BowArrow& operator=(BowArrow && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> ArrowRenderer;

	float4 Dir = float4::ZERO;
	float Deg = 0.0f;
	float ArrowSpeed = 1500.0f;
};

