#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TownDungeonEat : public GameEngineActor
{
	friend class TownLevel;
public:
	// constrcuter destructer
	TownDungeonEat();
	~TownDungeonEat();

	// delete Function
	TownDungeonEat(const TownDungeonEat & _Other) = delete;
	TownDungeonEat(TownDungeonEat && _Other) noexcept = delete;
	TownDungeonEat& operator=(const TownDungeonEat & _Other) = delete;
	TownDungeonEat& operator=(TownDungeonEat && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> EatRenderer;
};

