#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BossLife : public GameEngineActor
{
	friend class Belial;
public:
	// constrcuter destructer
	BossLife();
	~BossLife();

	// delete Function
	BossLife(const BossLife & _Other) = delete;
	BossLife(BossLife && _Other) noexcept = delete;
	BossLife& operator=(const BossLife & _Other) = delete;
	BossLife& operator=(BossLife && _Other) noexcept = delete;

	void SetLifeBarScale(float _Per);

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineUIRenderer> BossLifeBack;
	std::shared_ptr<GameEngineUIRenderer> BossLifeBase;
	std::shared_ptr<GameEngineUIRenderer> BossLifeBar;
	std::shared_ptr<GameEngineUIRenderer> BossImage;

	float MaxLifeBarScaleX = 400.0f;
};

