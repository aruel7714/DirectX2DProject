#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TownNPCTemple : public GameEngineActor
{
public:
	// constrcuter destructer
	TownNPCTemple();
	~TownNPCTemple();

	// delete Function
	TownNPCTemple(const TownNPCTemple & _Other) = delete;
	TownNPCTemple(TownNPCTemple && _Other) noexcept = delete;
	TownNPCTemple& operator=(const TownNPCTemple & _Other) = delete;
	TownNPCTemple& operator=(TownNPCTemple && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> RozenRenderer;
	std::shared_ptr<GameEngineCollision> RozenCollision;
};

