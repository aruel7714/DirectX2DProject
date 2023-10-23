#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class DungeonNPCGiant : public GameEngineActor
{
public:
	// constrcuter destructer
	DungeonNPCGiant();
	~DungeonNPCGiant();

	// delete Function
	DungeonNPCGiant(const DungeonNPCGiant & _Other) = delete;
	DungeonNPCGiant(DungeonNPCGiant && _Other) noexcept = delete;
	DungeonNPCGiant& operator=(const DungeonNPCGiant & _Other) = delete;
	DungeonNPCGiant& operator=(DungeonNPCGiant && _Other) noexcept = delete;

	void SetGiantPosition(float4 _Pos);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> GiantRenderer;
	std::shared_ptr<GameEngineCollision> GiantCollision;
};

