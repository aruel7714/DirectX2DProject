#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BulletState
{
	Normal,
	Hit,
	Max,
};

// Ό³Έν : 
class BelialBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	BelialBullet();
	~BelialBullet();

	// delete Function
	BelialBullet(const BelialBullet & _Other) = delete;
	BelialBullet(BelialBullet && _Other) noexcept = delete;
	BelialBullet& operator=(const BelialBullet & _Other) = delete;
	BelialBullet& operator=(BelialBullet && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BulletRenderer;

	BulletState State = BulletState::Max;

	std::shared_ptr<GameEngineCollision> BulletCollision;

	void ChangeState(BulletState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void NormalStart();
	void NormalUpdate(float _Delta);

	void HitStart();
	void HitUpdate(float _Delta);
};

