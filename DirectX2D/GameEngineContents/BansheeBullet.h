#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BansheeBullet : public GameEngineActor
{
	friend class Banshee;
public:
	// constrcuter destructer
	BansheeBullet();
	~BansheeBullet();

	// delete Function
	BansheeBullet(const BansheeBullet & _Other) = delete;
	BansheeBullet(BansheeBullet && _Other) noexcept = delete;
	BansheeBullet& operator=(const BansheeBullet & _Other) = delete;
	BansheeBullet& operator=(BansheeBullet && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void SetDir(int _num);
private:
	std::shared_ptr<GameEngineSpriteRenderer> BulletRenderer;

	float4 Dir = float4::ZERO;
	float BulletSpeed = 300.0f;
};

