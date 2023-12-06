#pragma once
#include "DungeonMap.h"

// Ό³Έν : 
class BossEncounterLevel : public DungeonMap
{
public:
	// constrcuter destructer
	BossEncounterLevel();
	~BossEncounterLevel();

	// delete Function
	BossEncounterLevel(const BossEncounterLevel & _Other) = delete;
	BossEncounterLevel(BossEncounterLevel && _Other) noexcept = delete;
	BossEncounterLevel& operator=(const BossEncounterLevel & _Other) = delete;
	BossEncounterLevel& operator=(BossEncounterLevel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class BossEncounterFloor> BossEncounterFloor;
	std::shared_ptr<class Player> MainPlayer;

	std::shared_ptr<class Belial> BossBelial;

	std::shared_ptr<class DungeonMoveTrigger> TriggerLeft;
	std::shared_ptr<class DungeonMoveTrigger> TriggerRight;

	std::shared_ptr<class DungeonStele> Stele1;
	std::shared_ptr<class DungeonStele> Stele2;

	std::shared_ptr<class BossSpawnTrigger> SpawnTrigger;
	std::shared_ptr<class BossSpawnFadeOut> SpawnFadeOut;

	void BossResourceLoad();

	int TriggerDeathCount = 0;
	int FadeDeathCount = 0;

	bool BossSoundOn = false;
	GameEngineSoundPlayer BossSpawnSound;
};

