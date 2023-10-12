#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class DungeonNPCInn : public GameEngineActor
{
public:
	// constrcuter destructer
	DungeonNPCInn();
	~DungeonNPCInn();

	// delete Function
	DungeonNPCInn(const DungeonNPCInn & _Other) = delete;
	DungeonNPCInn(DungeonNPCInn && _Other) noexcept = delete;
	DungeonNPCInn& operator=(const DungeonNPCInn & _Other) = delete;
	DungeonNPCInn& operator=(DungeonNPCInn && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> InnRenderer;
	std::shared_ptr<GameEngineCollision> InnCollision;
};

