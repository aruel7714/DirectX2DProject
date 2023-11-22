#pragma once
#include "DungeonMap.h"

// Ό³Έν : 
class Level1F_2 : public DungeonMap
{
public:
	// constrcuter destructer
	Level1F_2();
	~Level1F_2();

	// delete Function
	Level1F_2(const Level1F_2 & _Other) = delete;
	Level1F_2(Level1F_2 && _Other) noexcept = delete;
	Level1F_2& operator=(const Level1F_2 & _Other) = delete;
	Level1F_2& operator=(Level1F_2 && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class Level1F_2_Floor> Floor2;
	std::shared_ptr<class Player> MainPlayer;
	std::shared_ptr<class DungeonMoveTrigger> TriggerLeft;
	std::shared_ptr<class DungeonMoveTrigger> TriggerRight;

	std::shared_ptr<class DungeonStele> Stele1;
	std::shared_ptr<class DungeonStele> Stele2;

	std::map<std::string, std::shared_ptr<GameEngineActor>> AllMonsters;
	std::map<std::string, bool> MonsterDeathCheck;

	void DeathOn();

	bool AllDeathCheck();
};

