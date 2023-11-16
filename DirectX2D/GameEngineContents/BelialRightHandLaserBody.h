#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BelialRightHandLaserBody : public GameEngineActor
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
};

