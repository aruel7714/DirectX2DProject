#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class FadeOut : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeOut();
	~FadeOut();

	// delete Function
	FadeOut(const FadeOut & _Other) = delete;
	FadeOut(FadeOut && _Other) noexcept = delete;
	FadeOut& operator=(const FadeOut & _Other) = delete;
	FadeOut& operator=(FadeOut && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BlackRenderer;
};

