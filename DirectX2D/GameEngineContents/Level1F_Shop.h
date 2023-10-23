#pragma once
#include "DungeonMap.h"

// Ό³Έν : 
class Level1F_Shop : public DungeonMap
{
public:
	// constrcuter destructer
	Level1F_Shop();
	~Level1F_Shop();

	// delete Function
	Level1F_Shop(const Level1F_Shop & _Other) = delete;
	Level1F_Shop(Level1F_Shop && _Other) noexcept = delete;
	Level1F_Shop& operator=(const Level1F_Shop & _Other) = delete;
	Level1F_Shop& operator=(Level1F_Shop && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class Level1F_Shop_Floor> ShopFloor;
	std::shared_ptr<class Player> MainPlayer;
	std::shared_ptr<class DungeonMoveTrigger> TriggerLeft;
};

