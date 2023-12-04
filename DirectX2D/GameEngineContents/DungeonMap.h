#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν : 
class DungeonMap : public GameEngineLevel
{
public:
	// constrcuter destructer
	DungeonMap();
	~DungeonMap();

	// delete Function
	DungeonMap(const DungeonMap & _Other) = delete;
	DungeonMap(DungeonMap && _Other) noexcept = delete;
	DungeonMap& operator=(const DungeonMap & _Other) = delete;
	DungeonMap& operator=(DungeonMap && _Other) noexcept = delete;

protected:
	float4 PlayerPos;

	GameEngineLevel* NextLevel;
	GameEngineLevel* PrevLevel;

	std::shared_ptr<LevelFadeIn> FadeIn;
	std::shared_ptr<LevelFadeOut> FadeOut;

	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	GameEngineLevel* FindLevel(const std::string& _Name);
private:
};

