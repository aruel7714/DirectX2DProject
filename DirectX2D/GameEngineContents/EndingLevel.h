#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν : 
class EndingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EndingLevel();
	~EndingLevel();

	// delete Function
	EndingLevel(const EndingLevel & _Other) = delete;
	EndingLevel(EndingLevel && _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel & _Other) = delete;
	EndingLevel& operator=(EndingLevel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class EndingFloor> Floor;

	std::shared_ptr<LevelFadeIn> FadeIn;
	std::shared_ptr<LevelFadeOut> FadeOut;
};

