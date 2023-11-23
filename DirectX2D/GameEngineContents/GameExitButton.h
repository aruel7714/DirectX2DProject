#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class GameExitButton : public GameEngineActor
{
public:
	// constrcuter destructer
	GameExitButton();
	~GameExitButton();

	// delete Function
	GameExitButton(const GameExitButton & _Other) = delete;
	GameExitButton(GameExitButton && _Other) noexcept = delete;
	GameExitButton& operator=(const GameExitButton & _Other) = delete;
	GameExitButton& operator=(GameExitButton && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> ButtonRenderer;
	std::shared_ptr<GameEngineCollision> ButtonCollision;
};

