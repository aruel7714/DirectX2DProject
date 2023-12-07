#pragma once
#include "Monster.h"

// ���� : 
// Pattern1 : �ð���� �Ǵ� �ݽð�������� ȸ���ϸ� 4�������� Bullet �߻�
// Pattern2 : Sword ��ȯ 
//				��ȯ ���Ŀ��� ��� �÷��̾� ��ġ�� ȸ���ϸ� �߻��Ҷ��� ȸ���� ����
// Pattern3 : ���� �տ��� ������ �߻� �ּ� 1������ �ִ� 3������
//				���� ���� ����

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

