#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class PlayerLife : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerLife();
	~PlayerLife();

	// delete Function
	PlayerLife(const PlayerLife & _Other) = delete;
	PlayerLife(PlayerLife && _Other) noexcept = delete;
	PlayerLife& operator=(const PlayerLife & _Other) = delete;
	PlayerLife& operator=(PlayerLife && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> LifeBase;
	std::shared_ptr<GameEngineSpriteRenderer> LifeBack;
	std::shared_ptr<GameEngineSpriteRenderer> LifeBar;
	std::shared_ptr<GameEngineSpriteRenderer> LifeWave;
};

