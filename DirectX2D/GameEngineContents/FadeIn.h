#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class FadeIn : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeIn();
	~FadeIn();

	// delete Function
	FadeIn(const FadeIn & _Other) = delete;
	FadeIn(FadeIn && _Other) noexcept = delete;
	FadeIn& operator=(const FadeIn & _Other) = delete;
	FadeIn& operator=(FadeIn && _Other) noexcept = delete;

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

