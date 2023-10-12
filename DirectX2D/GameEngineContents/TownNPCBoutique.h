#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TownNPCBoutique : public GameEngineActor
{
public:
	// constrcuter destructer
	TownNPCBoutique();
	~TownNPCBoutique();

	// delete Function
	TownNPCBoutique(const TownNPCBoutique & _Other) = delete;
	TownNPCBoutique(TownNPCBoutique && _Other) noexcept = delete;
	TownNPCBoutique& operator=(const TownNPCBoutique & _Other) = delete;
	TownNPCBoutique& operator=(TownNPCBoutique && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BlochRenderer;
	std::shared_ptr<GameEngineCollision> BlochCollision;
};

