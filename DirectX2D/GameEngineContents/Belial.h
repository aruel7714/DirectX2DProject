#pragma once
#include <GameEngineCore/GameEngineActor.h>

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
	Max
};

class Belial : public GameEngineActor
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

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BelialBackGroundRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> BelialRenderer;

	BelialState State = BelialState::Max;

	float PatternStartTime = 0.0f;
	float FireBulletTime = 0.0f;
	float SummonSwordTime = 0.0f;
	
	int SummonSwordCount = 0;

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
};

