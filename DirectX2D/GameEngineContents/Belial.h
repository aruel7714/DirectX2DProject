#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 
// Pattern1 : 시계방향 또는 반시계방향으로 회전하며 4방향으로 Bullet 발사
// Pattern2 : Sword 소환 
//				소환 직후에는 계속 플레이어 위치로 회전하며 발사할때는 회전값 고정
// Pattern3 : 한쪽 손에서 레이저 발사 최소 1번에서 최대 3번까지
//				시작 손은 랜덤

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

