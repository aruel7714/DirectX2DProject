#pragma once
#include "BackGround.h"

// Ό³Έν : 
class TownSecondFloorRight : public BackGround
{
public:
	// constrcuter destructer
	TownSecondFloorRight();
	~TownSecondFloorRight();

	// delete Function
	TownSecondFloorRight(const TownSecondFloorRight & _Other) = delete;
	TownSecondFloorRight(TownSecondFloorRight && _Other) noexcept = delete;
	TownSecondFloorRight& operator=(const TownSecondFloorRight & _Other) = delete;
	TownSecondFloorRight& operator=(TownSecondFloorRight && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> SecondFloorRightRenderer;
};

