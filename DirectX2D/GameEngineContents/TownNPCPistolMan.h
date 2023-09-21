#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TownNPCPistolMan : public GameEngineActor
{
public:
	// constrcuter destructer
	TownNPCPistolMan();
	~TownNPCPistolMan();

	// delete Function
	TownNPCPistolMan(const TownNPCPistolMan & _Other) = delete;
	TownNPCPistolMan(TownNPCPistolMan && _Other) noexcept = delete;
	TownNPCPistolMan& operator=(const TownNPCPistolMan & _Other) = delete;
	TownNPCPistolMan& operator=(TownNPCPistolMan && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> FiatRenderer;
};

