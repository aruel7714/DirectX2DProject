#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BossSpawnTrigger : public GameEngineActor
{
public:
	// constrcuter destructer
	BossSpawnTrigger();
	~BossSpawnTrigger();

	// delete Function
	BossSpawnTrigger(const BossSpawnTrigger & _Other) = delete;
	BossSpawnTrigger(BossSpawnTrigger && _Other) noexcept = delete;
	BossSpawnTrigger& operator=(const BossSpawnTrigger & _Other) = delete;
	BossSpawnTrigger& operator=(BossSpawnTrigger && _Other) noexcept = delete;

	std::shared_ptr<GameEngineCollision> BossSpawnTriggerCollision;

	void SetMoveTriggerScale(float4 _Scale);
	void SetMoveTriggerPosition(float4 _Position);

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

