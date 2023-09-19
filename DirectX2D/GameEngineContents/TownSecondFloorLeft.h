#pragma once
#include "BackGround.h"

// Ό³Έν : 
class TownSecondFloorLeft : public BackGround
{
	friend class Player;
public:
	// constrcuter destructer
	TownSecondFloorLeft();
	~TownSecondFloorLeft();

	// delete Function
	TownSecondFloorLeft(const TownSecondFloorLeft & _Other) = delete;
	TownSecondFloorLeft(TownSecondFloorLeft && _Other) noexcept = delete;
	TownSecondFloorLeft& operator=(const TownSecondFloorLeft & _Other) = delete;
	TownSecondFloorLeft& operator=(TownSecondFloorLeft && _Other) noexcept = delete;

	static TownSecondFloorLeft* DebugSecondFloorLeft;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> SecondFloorLeftRenderer;
};

