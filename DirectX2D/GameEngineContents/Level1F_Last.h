#pragma once
#include "DungeonMap.h"

// Ό³Έν : 
class Level1F_Last : public DungeonMap
{
	friend class Player;
public:
	// constrcuter destructer
	Level1F_Last();
	~Level1F_Last();

	// delete Function
	Level1F_Last(const Level1F_Last & _Other) = delete;
	Level1F_Last(Level1F_Last && _Other) noexcept = delete;
	Level1F_Last& operator=(const Level1F_Last & _Other) = delete;
	Level1F_Last& operator=(Level1F_Last && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class Level1F_Last_Floor> FloorLast;
	std::shared_ptr<class Player> MainPlayer;
	std::shared_ptr<class DungeonMoveTrigger> TriggerLeft;
};

