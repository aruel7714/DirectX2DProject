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

	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void FindLevel(const std::string& _Name);

private:
	std::map<std::string, std::shared_ptr<GameEngineLevel>> AllLevel;
};

