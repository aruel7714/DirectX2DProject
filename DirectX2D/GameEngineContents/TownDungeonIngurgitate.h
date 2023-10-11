#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TownDungeonIngurgitate : public GameEngineActor
{
	friend class TownLevel;
public:
	// constrcuter destructer
	TownDungeonIngurgitate();
	~TownDungeonIngurgitate();

	// delete Function
	TownDungeonIngurgitate(const TownDungeonIngurgitate & _Other) = delete;
	TownDungeonIngurgitate(TownDungeonIngurgitate && _Other) noexcept = delete;
	TownDungeonIngurgitate& operator=(const TownDungeonIngurgitate & _Other) = delete;
	TownDungeonIngurgitate& operator=(TownDungeonIngurgitate && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> IngurgitateRenderer;
};

