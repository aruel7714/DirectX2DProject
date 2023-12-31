#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� : 
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel & _Other) = delete;
	TitleLevel(TitleLevel && _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel & _Other) = delete;
	TitleLevel& operator=(TitleLevel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class GameStartButton> GameStartButtonObject;
	std::shared_ptr<class SettingButton> SettingButtonObject;
	std::shared_ptr<class GameExitButton> GameExitButtonObject;

	std::shared_ptr<LevelFadeIn> FadeIn;

	GameEngineSoundPlayer Bgm;
};

