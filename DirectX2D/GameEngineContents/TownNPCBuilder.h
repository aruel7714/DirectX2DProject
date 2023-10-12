#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TownNPCBuilder : public GameEngineActor
{
public:
	// constrcuter destructer
	TownNPCBuilder();
	~TownNPCBuilder();

	// delete Function
	TownNPCBuilder(const TownNPCBuilder & _Other) = delete;
	TownNPCBuilder(TownNPCBuilder && _Other) noexcept = delete;
	TownNPCBuilder& operator=(const TownNPCBuilder & _Other) = delete;
	TownNPCBuilder& operator=(TownNPCBuilder && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> YulfordRenderer;
	std::shared_ptr<GameEngineCollision> YulfordCollision;
};

