#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class GameMouseCursor : public GameEngineActor
{
public:
	// constrcuter destructer
	GameMouseCursor();
	~GameMouseCursor();

	// delete Function
	GameMouseCursor(const GameMouseCursor & _Other) = delete;
	GameMouseCursor(GameMouseCursor && _Other) noexcept = delete;
	GameMouseCursor& operator=(const GameMouseCursor & _Other) = delete;
	GameMouseCursor& operator=(GameMouseCursor && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> MouseRenderer;
};

