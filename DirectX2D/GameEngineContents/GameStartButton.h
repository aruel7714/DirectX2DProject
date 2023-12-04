#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class GameStartButton : public GameEngineActor
{
	friend class TitleLevel;
public:
	// constrcuter destructer
	GameStartButton();
	~GameStartButton();

	// delete Function
	GameStartButton(const GameStartButton & _Other) = delete;
	GameStartButton(GameStartButton && _Other) noexcept = delete;
	GameStartButton& operator=(const GameStartButton & _Other) = delete;
	GameStartButton& operator=(GameStartButton && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> ButtonRenderer;
	std::shared_ptr<GameEngineCollision> ButtonCollision;

	std::shared_ptr<LevelFadeIn> Fade;

	bool FadeOnOff = false;
};


