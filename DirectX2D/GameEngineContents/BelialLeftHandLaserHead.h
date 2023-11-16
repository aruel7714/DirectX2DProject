#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BelialLeftHandLaserHead : public GameEngineActor
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
};

