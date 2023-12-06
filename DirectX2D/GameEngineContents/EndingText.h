#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class EndingText : public GameEngineActor
{
public:
	// constrcuter destructer
	EndingText();
	~EndingText();

	// delete Function
	EndingText(const EndingText & _Other) = delete;
	EndingText(EndingText && _Other) noexcept = delete;
	EndingText& operator=(const EndingText & _Other) = delete;
	EndingText& operator=(EndingText && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> TextRenderer;
};

