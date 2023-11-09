#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν : 
class OpeningLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	OpeningLevel();
	~OpeningLevel();

	// delete Function
	OpeningLevel(const OpeningLevel & _Other) = delete;
	OpeningLevel(OpeningLevel && _Other) noexcept = delete;
	OpeningLevel& operator=(const OpeningLevel & _Other) = delete;
	OpeningLevel& operator=(OpeningLevel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:

};

