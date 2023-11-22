#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class DungeonTorch : public GameEngineActor
{
public:
	// constrcuter destructer
	DungeonTorch();
	~DungeonTorch();

	// delete Function
	DungeonTorch(const DungeonTorch & _Other) = delete;
	DungeonTorch(DungeonTorch && _Other) noexcept = delete;
	DungeonTorch& operator=(const DungeonTorch & _Other) = delete;
	DungeonTorch& operator=(DungeonTorch && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> TorchRenderer;
};

