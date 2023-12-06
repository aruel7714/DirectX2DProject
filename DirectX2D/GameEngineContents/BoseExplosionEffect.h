#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BoseExplosionEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BoseExplosionEffect();
	~BoseExplosionEffect();

	// delete Function
	BoseExplosionEffect(const BoseExplosionEffect & _Other) = delete;
	BoseExplosionEffect(BoseExplosionEffect && _Other) noexcept = delete;
	BoseExplosionEffect& operator=(const BoseExplosionEffect & _Other) = delete;
	BoseExplosionEffect& operator=(BoseExplosionEffect && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> ExplosionRenderer;
};

