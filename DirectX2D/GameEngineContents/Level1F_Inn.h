#pragma once
#include "DungeonMap.h"

// Ό³Έν : 
class Level1F_Inn : public DungeonMap
{
public:
	// constrcuter destructer
	Level1F_Inn();
	~Level1F_Inn();

	// delete Function
	Level1F_Inn(const Level1F_Inn & _Other) = delete;
	Level1F_Inn(Level1F_Inn && _Other) noexcept = delete;
	Level1F_Inn& operator=(const Level1F_Inn & _Other) = delete;
	Level1F_Inn& operator=(Level1F_Inn && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class Level1F_Inn_Floor> InnFloor;
	std::shared_ptr<class Player> MainPlayer;
	std::shared_ptr<class DungeonMoveTrigger> TriggerRight;
};

