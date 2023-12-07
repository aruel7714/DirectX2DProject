#pragma once
#include "Monster.h"

// 설명 : 
// Pattern1 : 시계방향 또는 반시계방향으로 회전하며 4방향으로 Bullet 발사
// Pattern2 : Sword 소환 
//				소환 직후에는 계속 플레이어 위치로 회전하며 발사할때는 회전값 고정
// Pattern3 : 한쪽 손에서 레이저 발사 최소 1번에서 최대 3번까지
//				시작 손은 랜덤

enum class BelialState
{
	Idle,
	FireBulletReady,
	FireBullet,
	SummonSword,
	Laser,
	Explosion,
	Death,
	Max
};

class Belial : public Monster
{
public:
	// constrcuter destructer
	Belial();
	~Belial();

	// delete Function
	Belial(const Belial & _Other) = delete;
	Belial(Belial && _Other) noexcept = delete;
	Belial& operator=(const Belial & _Other) = delete;
	Belial& operator=(Belial && _Other) noexcept = delete;

	bool IsBelialDeathState()
	{
		return BelialDeathState;
	}

	bool IsBelialExplosionState()
	{
		return BelialExplosionState;
	}

	void BelialMulColorPlus(float _Delta);

	bool IsBelialMulColor();

	void UIBelialLifeOn();

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BelialBackGroundRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> BelialRenderer;

	std::shared_ptr<class BelialLeftHand> LeftHand;
	std::shared_ptr<class BelialRightHand> RightHand;

	std::shared_ptr<GameEngineCollision> BelialCollision;

	std::shared_ptr<class BossLife> UIBelialLife;

	BelialState State = BelialState::Max;

	GameEngineRandom Random;
	int Pattern = 1;

	int IdleToPatternSelect = 1;
	bool IsRandom = false;

	float PatternStartTime = 0.0f;
	float FireBulletTime = 0.0f;
	float SummonSwordTime = 0.0f;

	float SummonBulletTime = 0.0f;
	float4 BulletDir = float4::UP;
	float BulletDeg = 0.0f;
	bool BulletDegRight = true;
	
	int SummonSwordCount = 0;

	float LaserTime = 0.0f;
	bool LaserRight = true;
	int LaserCount = 0;

	float4 Position = float4::ZERO;
	float DeathExplosionTime = 0.0f;
	float ExplosionPositionCount = 0;
	int EffectCount = 1;

	bool BelialDeathState = false;
	bool BelialExplosionState = false;

	GameEngineSoundPlayer AttackSound;

	void ChangeState(BelialState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);
	
	void FireBulletReadyStart();
	void FireBulletReadyUpdate(float _Delta);

	void FireBulletStart();
	void FireBulletUpdate(float _Delta);
	
	void SummonSwordStart();
	void SummonSwordUpdate(float _Delta);

	void LaserStart();
	void LaserUpdate(float _Delta);

	void ExplosionStart();
	void ExplosionUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);
};

