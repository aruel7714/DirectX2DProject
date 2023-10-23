#pragma once
#include "DungeonMap.h"

// Ό³Έν : 
class Level1F : public DungeonMap
{
public:
	// constrcuter destructer
	Level1F();
	~Level1F();

	// delete Function
	Level1F(const Level1F & _Other) = delete;
	Level1F(Level1F && _Other) noexcept = delete;
	Level1F& operator=(const Level1F & _Other) = delete;
	Level1F& operator=(Level1F && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class Player> MainPlayer;
	std::shared_ptr<class Level1F_Floor1> Level1F_Floor;

	std::shared_ptr<class DungeonMoveTrigger> TriggerLeft;
};

