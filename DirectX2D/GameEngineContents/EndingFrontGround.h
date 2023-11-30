#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class EndingFrontGround : public GameEngineActor
{
public:
	// constrcuter destructer
	EndingFrontGround();
	~EndingFrontGround();

	// delete Function
	EndingFrontGround(const EndingFrontGround & _Other) = delete;
	EndingFrontGround(EndingFrontGround && _Other) noexcept = delete;
	EndingFrontGround& operator=(const EndingFrontGround & _Other) = delete;
	EndingFrontGround& operator=(EndingFrontGround && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> FrontGroundRenderer;

};

