#pragma once
#include "BackGround.h"

// Ό³Έν : 
class TownBuilding : public BackGround
{
public:
	// constrcuter destructer
	TownBuilding();
	~TownBuilding();

	// delete Function
	TownBuilding(const TownBuilding & _Other) = delete;
	TownBuilding(TownBuilding && _Other) noexcept = delete;
	TownBuilding& operator=(const TownBuilding & _Other) = delete;
	TownBuilding& operator=(TownBuilding && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> TrainingSchool;
	std::shared_ptr<class GameEngineSpriteRenderer> Shop;
	std::shared_ptr<class GameEngineSpriteRenderer> BlackSmith;
};

