#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class LevelFadeIn : public GameEngineActor
{
public:
	// constrcuter destructer
	LevelFadeIn();
	~LevelFadeIn();

	// delete Function
	LevelFadeIn(const LevelFadeIn& _Other) = delete;
	LevelFadeIn(LevelFadeIn&& _Other) noexcept = delete;
	LevelFadeIn& operator=(const LevelFadeIn& _Other) = delete;
	LevelFadeIn& operator=(LevelFadeIn&& _Other) noexcept = delete;

	float GetMulColorA()
	{
		return BlackRenderer->GetColorData().MulColor.A;
	}

protected:
	void Start() override;
	void Update(float _delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BlackRenderer;
};

