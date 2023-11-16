#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BelialSword : public GameEngineActor
{
public:
	// constrcuter destructer
	BelialSword();
	~BelialSword();

	// delete Function
	BelialSword(const BelialSword & _Other) = delete;
	BelialSword(BelialSword && _Other) noexcept = delete;
	BelialSword& operator=(const BelialSword & _Other) = delete;
	BelialSword& operator=(BelialSword && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> SwordRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> SwordChargeRenderer;
};

