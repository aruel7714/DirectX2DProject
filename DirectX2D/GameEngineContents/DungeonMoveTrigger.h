#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class DungeonMoveTrigger : public GameEngineActor
{
public:
	// constrcuter destructer
	DungeonMoveTrigger();
	~DungeonMoveTrigger();

	// delete Function
	DungeonMoveTrigger(const DungeonMoveTrigger & _Other) = delete;
	DungeonMoveTrigger(DungeonMoveTrigger && _Other) noexcept = delete;
	DungeonMoveTrigger& operator=(const DungeonMoveTrigger & _Other) = delete;
	DungeonMoveTrigger& operator=(DungeonMoveTrigger && _Other) noexcept = delete;

	std::shared_ptr<class GameEngineCollision> MoveTriggerCollision;

	void SetMoveTriggerScale(float4 _Scale);
	void SetMoveTriggerPosition(float4 _Position);



protected:
	void Start() override;
	void Update(float _Delta);
private:

};

