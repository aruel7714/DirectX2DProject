#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class LevelFadeOut : public GameEngineActor
{
public:
	// constrcuter destructer
	LevelFadeOut();
	~LevelFadeOut();

	// delete Function
	LevelFadeOut(const LevelFadeOut & _Other) = delete;
	LevelFadeOut(LevelFadeOut && _Other) noexcept = delete;
	LevelFadeOut& operator=(const LevelFadeOut & _Other) = delete;
	LevelFadeOut& operator=(LevelFadeOut && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BlackRenderer;
};

