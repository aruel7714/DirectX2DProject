#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class SettingButton : public GameEngineActor
{
public:
	// constrcuter destructer
	SettingButton();
	~SettingButton();

	// delete Function
	SettingButton(const SettingButton & _Other) = delete;
	SettingButton(SettingButton && _Other) noexcept = delete;
	SettingButton& operator=(const SettingButton & _Other) = delete;
	SettingButton& operator=(SettingButton && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> ButtonRenderer;
	std::shared_ptr<GameEngineCollision> ButtonCollision;
};

