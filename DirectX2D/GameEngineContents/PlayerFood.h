#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class PlayerFood : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerFood();
	~PlayerFood();

	// delete Function
	PlayerFood(const PlayerFood & _Other) = delete;
	PlayerFood(PlayerFood && _Other) noexcept = delete;
	PlayerFood& operator=(const PlayerFood & _Other) = delete;
	PlayerFood& operator=(PlayerFood && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineUIRenderer> FoodRenderer;
	std::shared_ptr<GameEngineUIRenderer> FoodText;
};

