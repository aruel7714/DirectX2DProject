#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TownDungeonTrigger : public GameEngineActor
{
	friend class TownLevel;
public:
	// constrcuter destructer
	TownDungeonTrigger();
	~TownDungeonTrigger();

	// delete Function
	TownDungeonTrigger(const TownDungeonTrigger & _Other) = delete;
	TownDungeonTrigger(TownDungeonTrigger && _Other) noexcept = delete;
	TownDungeonTrigger& operator=(const TownDungeonTrigger & _Other) = delete;
	TownDungeonTrigger& operator=(TownDungeonTrigger && _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineCollision> DungeonTriggerCollision;
};

