#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class GargoyleStatue : public GameEngineActor
{
public:
	// constrcuter destructer
	GargoyleStatue();
	~GargoyleStatue();

	// delete Function
	GargoyleStatue(const GargoyleStatue & _Other) = delete;
	GargoyleStatue(GargoyleStatue && _Other) noexcept = delete;
	GargoyleStatue& operator=(const GargoyleStatue & _Other) = delete;
	GargoyleStatue& operator=(GargoyleStatue && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> StatueBaseRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> GargoyleRenderer;
};

