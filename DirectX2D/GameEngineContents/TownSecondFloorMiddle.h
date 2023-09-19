#pragma once
#include "BackGround.h"

// Ό³Έν : 
class TownSecondFloorMiddle : public BackGround
{
public:
	// constrcuter destructer
	TownSecondFloorMiddle();
	~TownSecondFloorMiddle();

	// delete Function
	TownSecondFloorMiddle(const TownSecondFloorMiddle & _Other) = delete;
	TownSecondFloorMiddle(TownSecondFloorMiddle && _Other) noexcept = delete;
	TownSecondFloorMiddle& operator=(const TownSecondFloorMiddle & _Other) = delete;
	TownSecondFloorMiddle& operator=(TownSecondFloorMiddle && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> SecondFloorMiddleRenderer;
};

