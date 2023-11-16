#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BelialLeftHandLaserBody : public GameEngineActor
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
};

