#include "PreCompile.h"
#include "Belial.h"

#include "BelialSword.h"
#include "BelialBullet.h"
#include "BelialRightHand.h"
#include "BelialLeftHand.h"

#include "BossLife.h"

Belial::Belial()
{
}

Belial::~Belial()
{
}

void Belial::Start()
{
	if (nullptr == GameEngineSprite::Find("BelialBackGround"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	{
		BelialBackGroundRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossBackGround);
		BelialBackGroundRenderer->CreateAnimation("BackGround", "BelialBackground");
		BelialBackGroundRenderer->ChangeAnimation("BackGround");
		float4 Scale = BelialBackGroundRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
		BelialBackGroundRenderer->SetImageScale(Scale);
	}

	BelialRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossBody);
	{
		BelialRenderer->CreateAnimation("Belial_Idle", "BelialBodyIdle");
		BelialRenderer->CreateAnimation("Belial_FireBulletReady", "BelialBodyAttack", 0.05f, 0, 5, false);
		BelialRenderer->CreateAnimation("Belial_FireBullet", "BelialBodyAttack", 0.1f, 6, 9, true);
		BelialRenderer->CreateAnimation("Belial_FireBulletEnd", "BelialBodyAttack", 0.05f, 5, 0, false);
		GameEngineSprite::CreateSingle("SkellBossDead_Head.png");
	}
	BelialRenderer->SetSprite("BelialBodyIdle");
	float4 Scale = BelialRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BelialRenderer->SetImageScale(Scale);
	BelialRenderer->SetPivotValue({ 0.4f, 0.7f });

	BelialBackGroundRenderer->GetColorData().MulColor.A = 0.0f;
	BelialRenderer->GetColorData().MulColor.A = 0.0f;

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BossRoom.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	LeftHand = GetLevel()->CreateActor<BelialLeftHand>(RenderOrder::BossBody2);
	LeftHand->Transform.SetLocalPosition({ (64.0f * 4.0f) + 32.0f , -(MapScale.Y - (64.0f * 7.0f) - 32.0f) });
	RightHand = GetLevel()->CreateActor<BelialRightHand>(RenderOrder::BossBody2);
	RightHand->Transform.SetLocalPosition({ MapScale.X - (64.0f * 4.0f) - 32.0f, -(MapScale.Y - (64.0f * 10.0f) - 32.0f) });

	
	//BossBelial->Transform.SetLocalPosition({ (64.0f * 11.0f), -((64.0f * 11.0f) + 32.0f) });

	{
		// Status
		// Hp = 1000.0f;
		MaxHp = 100.0f;
		Hp = 100.0f;
		// BulletDamage = 6.0f;
		// LaserDamage = 9.0f;
		// SwordDamage = 8.0f;
	}

	{
		BelialCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		BelialCollision->SetCollisionType(ColType::AABBBOX2D);
		BelialCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 6.0f, 1.0f });
		BelialCollision->Transform.SetLocalScale({ Scale.X / 4.0f * 3.0f, Scale.Y / 4.0f * 3.0f });
	}
	UIBelialLife = GetLevel()->CreateActor<BossLife>(RenderOrder::MiddleUI);

	ChangeState(BelialState::Idle);

}

void Belial::Update(float _Delta)
{
	StateUpdate(_Delta);

	EventParameter DamageEvent;
	DamageEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			DamageCheck();
		};
	BelialCollision->CollisionEvent(CollisionType::Weapon, DamageEvent);

	float Per = Hp / MaxHp * 100.0f;

	UIBelialLife->SetLifeBarScale(Per);

	if (Hp <= 0)
	{
		ChangeState(BelialState::Death);
	}
}

void Belial::ChangeState(BelialState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BelialState::Idle:
			IdleStart();
			break;
		case BelialState::FireBulletReady:
			FireBulletReadyStart();
			break;
		case BelialState::FireBullet:
			FireBulletStart();
			break;
		case BelialState::SummonSword:
			SummonSwordStart();
			break;
		case BelialState::Laser:
			LaserStart();
			break;
		case BelialState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void Belial::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BelialState::Idle:
		return IdleUpdate(_Delta);
	case BelialState::FireBulletReady:
		return FireBulletReadyUpdate(_Delta);
	case BelialState::FireBullet:
		return FireBulletUpdate(_Delta);
	case BelialState::SummonSword:
		return SummonSwordUpdate(_Delta);
	case BelialState::Laser:
		return LaserUpdate(_Delta);
	case BelialState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}
void Belial::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "Belial_";
	AnimationName += _State;
	BelialRenderer->ChangeAnimation(AnimationName);
}

void Belial::IdleStart()
{
	ChangeAnimationState("Idle");
	float4 Scale = BelialRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BelialRenderer->SetImageScale(Scale);

	FireBulletTime = 0.0f;
	SummonSwordCount = 0;
	SummonSwordTime = 0.0f;
	LaserTime = 0.0f;
	PatternStartTime = 0.0f;

	BelialCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 6.0f, 1.0f });
	BelialCollision->Transform.SetLocalScale({ Scale.X / 4.0f * 3.0f, Scale.Y / 4.0f * 3.0f });
}
void Belial::IdleUpdate(float _Delta)
{
	if (BelialRenderer->GetColorData().MulColor.A >= 0.1f)
	{
		PatternStartTime += _Delta;
	}

	if (PatternStartTime >= 5.0f)
	{
		Pattern = Random.RandomInt(1, 3);

		if (Pattern == 1)
		{
			ChangeState(BelialState::FireBulletReady);
		}
		else if (Pattern == 2)
		{
			ChangeState(BelialState::SummonSword);
		}
		else if (Pattern == 3)
		{
			ChangeState(BelialState::Laser);
		}

	}
}

void Belial::FireBulletReadyStart()
{
	ChangeAnimationState("FireBulletReady");
	float4 Scale = BelialRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BelialRenderer->SetImageScale(Scale);

	BelialCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 6.0f, 1.0f });
	BelialCollision->Transform.SetLocalScale({ Scale.X / 4.0f * 3.0f, Scale.Y / 7.0f * 6.0f });
}
void Belial::FireBulletReadyUpdate(float _Delta)
{
	if (BelialRenderer->IsCurAnimationEnd())
	{
		ChangeState(BelialState::FireBullet);
	}
}

void Belial::FireBulletStart()
{
	ChangeAnimationState("FireBullet");
	float4 Scale = BelialRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BelialRenderer->SetImageScale(Scale);
	BulletDeg = BulletDir.Angle2DDeg();
	BulletDegRight = !BulletDegRight;
}
void Belial::FireBulletUpdate(float _Delta)
{
	SummonBulletTime += _Delta;
	FireBulletTime += _Delta;

	if (SummonBulletTime >= 0.1f)
	{
		std::shared_ptr<BelialBullet> Bullet1 = GetLevel()->CreateActor<BelialBullet>(RenderOrder::BossProjectile);
		Bullet1->Transform.SetLocalPosition(Transform.GetLocalPosition());
		Bullet1->Deg = BulletDeg;

		std::shared_ptr<BelialBullet> Bullet2 = GetLevel()->CreateActor<BelialBullet>(RenderOrder::BossProjectile);
		Bullet2->Transform.SetLocalPosition(Transform.GetLocalPosition());
		Bullet2->Deg = BulletDeg + 90.0f;

		std::shared_ptr<BelialBullet> Bullet3 = GetLevel()->CreateActor<BelialBullet>(RenderOrder::BossProjectile);
		Bullet3->Transform.SetLocalPosition(Transform.GetLocalPosition());
		Bullet3->Deg = BulletDeg + 180.0f;

		std::shared_ptr<BelialBullet> Bullet4 = GetLevel()->CreateActor<BelialBullet>(RenderOrder::BossProjectile);
		Bullet4->Transform.SetLocalPosition(Transform.GetLocalPosition());
		Bullet4->Deg = BulletDeg + 270.0f;

		if (BulletDegRight == false)
		{
			BulletDeg += 6.0f;
		}
		else
		{
			BulletDeg -= 6.0f;
		}

		SummonBulletTime = 0.0f;
	}

	if (FireBulletTime >= 3.2f)
	{
		ChangeAnimationState("FireBulletEnd");
	}

	if (BelialRenderer->IsCurAnimation("Belial_FireBulletEnd") && true == BelialRenderer->IsCurAnimationEnd())
	{
		ChangeState(BelialState::Idle);
	}
}

void Belial::SummonSwordStart()
{
	
}
void Belial::SummonSwordUpdate(float _Delta)
{
	SummonSwordTime += _Delta;

	if (SummonSwordTime >= 0.2f && SummonSwordCount < 6)
	{
		std::shared_ptr<BelialSword> Sword = GetLevel()->CreateActor<BelialSword>(RenderOrder::BossWallBackProjectile);
		Sword->Transform.SetLocalPosition({ (64.0f * 6) + 128.0f * SummonSwordCount, -(64.0f * 9) });
		SummonSwordCount++;
		SummonSwordTime = 0.0f;
	}

	if (SummonSwordCount >= 6 && SummonSwordTime >= 1.0f)
	{
		ChangeState(BelialState::Idle);
	}
}

void Belial::LaserStart()
{
	LaserCount = Random.RandomInt(1, 3);
}
void Belial::LaserUpdate(float _Delta)
{
	LaserTime += _Delta;

	if (LaserTime > 1.0f)
	{
		if (LaserRight == true)
		{
			RightHand->ChangeState(RightHandState::AttackReady);
		}
		else
		{
			LeftHand->ChangeState(LeftHandState::AttackReady);
		}

		LaserCount--;
		LaserRight = !LaserRight;
		LaserTime = 0.0f;
	}
	
	if (LaserCount <= 0)
	{
		ChangeState(BelialState::Idle);
	}
}

void Belial::DeathStart()
{
	BelialRenderer->SetSprite("SkellBossDead_Head.png");
	float4 Scale = BelialRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BelialRenderer->SetImageScale(Scale);

	BelialRenderer->SetPivotValue({ 0.4f, 1.0f });

	BelialCollision->Death();
	LeftHand->Death();
	RightHand->Death();
	BelialBackGroundRenderer->Death();
	BelialDeathState = true;
}
void Belial::DeathUpdate(float _Delta)
{
	GravityState(_Delta, Transform.GetLocalPosition(), BelialRenderer->GetImageTransform().GetLocalScale());
}

void Belial::BelialMulColorPlus(float _Delta)
{
	BelialBackGroundRenderer->GetColorData().MulColor.A += _Delta / 1.0f;
	BelialRenderer->GetColorData().MulColor.A += _Delta / 1.0f;

	if (1.0f <= BelialRenderer->GetColorData().MulColor.A)
	{
		LeftHand->LeftHandRenderer->GetColorData().MulColor.A += _Delta / 1.0f;
		RightHand->RightHandRenderer->GetColorData().MulColor.A += _Delta / 1.0f;
	}
}