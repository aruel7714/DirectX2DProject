#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BelialRightHandLaserHead : public GameEngineActor
{
	friend class BelialRightHand;
public:
	// constrcuter destructer
	BelialRightHandLaserHead();
	~BelialRightHandLaserHead();

	// delete Function
	BelialRightHandLaserHead(const BelialRightHandLaserHead & _Other) = delete;
	BelialRightHandLaserHead(BelialRightHandLaserHead && _Other) noexcept = delete;
	BelialRightHandLaserHead& operator=(const BelialRightHandLaserHead & _Other) = delete;
	BelialRightHandLaserHead& operator=(BelialRightHandLaserHead && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> RightLaserHeadRenderer;
};

