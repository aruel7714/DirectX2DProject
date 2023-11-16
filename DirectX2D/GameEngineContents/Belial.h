#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : 
// Pattern1 : �ð���� �Ǵ� �ݽð�������� ȸ���ϸ� 4�������� Bullet �߻�
// Pattern2 : Sword ��ȯ 
//				��ȯ ���Ŀ��� ��� �÷��̾� ��ġ�� ȸ���ϸ� �߻��Ҷ��� ȸ���� ����
// Pattern3 : ���� �տ��� ������ �߻� �ּ� 1������ �ִ� 3������
//				���� ���� ����

enum class BelialPattern
{
	Idle,
	FireBullet,
	SummonSword,
	Razer,
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


};

