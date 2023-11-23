#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TitleMouse : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleMouse();
	~TitleMouse();

	// delete Function
	TitleMouse(const TitleMouse & _Other) = delete;
	TitleMouse(TitleMouse && _Other) noexcept = delete;
	TitleMouse& operator=(const TitleMouse & _Other) = delete;
	TitleMouse& operator=(TitleMouse && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> MouseRenderer;
	std::shared_ptr<GameEngineCollision> MouseCollision;
};

