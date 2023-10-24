#pragma once
#include "DungeonMap.h"

// Ό³Έν : 
class AfterBossEncounterLevel : public DungeonMap
{
public:
	// constrcuter destructer
	AfterBossEncounterLevel();
	~AfterBossEncounterLevel();

	// delete Function
	AfterBossEncounterLevel(const AfterBossEncounterLevel & _Other) = delete;
	AfterBossEncounterLevel(AfterBossEncounterLevel && _Other) noexcept = delete;
	AfterBossEncounterLevel& operator=(const AfterBossEncounterLevel & _Other) = delete;
	AfterBossEncounterLevel& operator=(AfterBossEncounterLevel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class AfterBossEncounterFloor> AfterBossEncounterFloor;
	std::shared_ptr<class Player> MainPlayer;
	std::shared_ptr<class DungeonMoveTrigger> TriggerLeft;

};

