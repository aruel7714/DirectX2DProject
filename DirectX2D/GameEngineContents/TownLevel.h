#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν : 
class TownLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TownLevel();
	~TownLevel();

	// delete Function
	TownLevel(const TownLevel & _Other) = delete;
	TownLevel(TownLevel && _Other) noexcept = delete;
	TownLevel& operator=(const TownLevel & _Other) = delete;
	TownLevel& operator=(TownLevel && _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class Player> MainPlayer;
	std::shared_ptr<class TownFloor> _TownFloor;
	std::shared_ptr<class TownDungeonTrigger> Trigger;
	std::shared_ptr<class TownDungeonEat> DungeonEat;

	std::shared_ptr<LevelFadeIn> FadeIn;
	std::shared_ptr<LevelFadeOut> FadeOut;

	int Count = 0;
};

