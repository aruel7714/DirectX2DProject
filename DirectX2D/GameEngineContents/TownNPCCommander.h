#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TownNPCCommander : public GameEngineActor
{
public:
	// constrcuter destructer
	TownNPCCommander();
	~TownNPCCommander();

	// delete Function
	TownNPCCommander(const TownNPCCommander & _Other) = delete;
	TownNPCCommander(TownNPCCommander && _Other) noexcept = delete;
	TownNPCCommander& operator=(const TownNPCCommander & _Other) = delete;
	TownNPCCommander& operator=(TownNPCCommander && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> CoblovinaRenderer;
};

