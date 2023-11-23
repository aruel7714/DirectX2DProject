#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BulletState
{
	Normal,
	Hit,
	Max
};

// Ό³Έν : 
class BatBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	BatBullet();
	~BatBullet();

	// delete Function
	BatBullet(const BatBullet & _Other) = delete;
	BatBullet(BatBullet && _Other) noexcept = delete;
	BatBullet& operator=(const BatBullet & _Other) = delete;
	BatBullet& operator=(BatBullet && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BulletRenderer;
	std::shared_ptr<GameEngineCollision> BulletCollision;

	BulletState State = BulletState::Max;

	void ChangeState(BulletState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void NormalStart();
	void NormalUpdate(float _Delta);

	void HitStart();
	void HitUpdate(float _Delta);
};

