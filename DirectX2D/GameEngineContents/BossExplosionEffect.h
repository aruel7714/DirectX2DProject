#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BossExplosionEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BossExplosionEffect();
	~BossExplosionEffect();

	// delete Function
	BossExplosionEffect(const BossExplosionEffect & _Other) = delete;
	BossExplosionEffect(BossExplosionEffect && _Other) noexcept = delete;
	BossExplosionEffect& operator=(const BossExplosionEffect & _Other) = delete;
	BossExplosionEffect& operator=(BossExplosionEffect && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> ExplosionRenderer;
};

