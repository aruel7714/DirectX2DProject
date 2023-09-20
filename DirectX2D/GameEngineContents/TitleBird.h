#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TitleBird : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleBird();
	~TitleBird();

	// delete Function
	TitleBird(const TitleBird & _Other) = delete;
	TitleBird(TitleBird && _Other) noexcept = delete;
	TitleBird& operator=(const TitleBird & _Other) = delete;
	TitleBird& operator=(TitleBird && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> TitleBirdRenderer;


};

