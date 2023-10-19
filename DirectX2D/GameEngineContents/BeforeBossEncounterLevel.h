#pragma once
#include "DungeonMap.h"

// Ό³Έν : 
class BeforeBossEncounterLevel : public DungeonMap
{
public:
	// constrcuter destructer
	BeforeBossEncounterLevel();
	~BeforeBossEncounterLevel();

	// delete Function
	BeforeBossEncounterLevel(const BeforeBossEncounterLevel & _Other) = delete;
	BeforeBossEncounterLevel(BeforeBossEncounterLevel && _Other) noexcept = delete;
	BeforeBossEncounterLevel& operator=(const BeforeBossEncounterLevel & _Other) = delete;
	BeforeBossEncounterLevel& operator=(BeforeBossEncounterLevel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class BeforeBossEncounterFloor> BeforeBossEncounterFloor;
	std::shared_ptr<class Player> MainPlayer;

	std::shared_ptr<class DungeonMoveTrigger> TriggerRight;
};

