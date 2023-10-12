#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TownNPCMerchant : public GameEngineActor
{
public:
	// constrcuter destructer
	TownNPCMerchant();
	~TownNPCMerchant();

	// delete Function
	TownNPCMerchant(const TownNPCMerchant & _Other) = delete;
	TownNPCMerchant(TownNPCMerchant && _Other) noexcept = delete;
	TownNPCMerchant& operator=(const TownNPCMerchant & _Other) = delete;
	TownNPCMerchant& operator=(TownNPCMerchant && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> MilliaRenderer;
	std::shared_ptr<GameEngineCollision> MilliaCollision;
};

