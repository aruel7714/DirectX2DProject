#include "PreCompile.h"
#include "Belial.h"

#include "BelialSword.h"
#include "BelialBullet.h"
#include "BelialRightHand.h"
#include "BelialLeftHand.h"

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
		BelialRenderer->CreateAnimation("Belial_FireBulletReady", "BelialBodyAttack", 0.1f, 0, 5, false);
		BelialRenderer->CreateAnimation("Belial_FireBullet", "BelialBodyAttack", 0.1f, 6, 9, true);
	}
	BelialRenderer->SetSprite("BelialBodyIdle");
	float4 Scale = BelialRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BelialRenderer->SetImageScale(Scale);
	BelialRenderer->SetPivotValue({ 0.4f, 0.7f });

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BossRoom.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	LeftHand = GetLevel()->CreateActor<BelialLeftHand>(RenderOrder::BossBody);
	LeftHand->Transform.SetLocalPosition({ (64.0f * 4.0f) + 32.0f , -(MapScale.Y - (64.0f * 7.0f) - 32.0f) });
	RightHand = GetLevel()->CreateActor<BelialRightHand>(RenderOrder::BossBody);
	RightHand->Transform.SetLocalPosition({ MapScale.X - (64.0f * 4.0f) - 32.0f, -(MapScale.Y - (64.0f * 10.0f) - 32.0f) });

	ChangeState(BelialState::Idle);
	//BossBelial->Transform.SetLocalPosition({ (64.0f * 11.0f), -((64.0f * 11.0f) + 32.0f) });
}

void Belial::Update(float _Delta)
{
	StateUpdate(_Delta);
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

	FireBulletTime = 0.0f;
	SummonSwordCount = 0;
	SummonSwordTime = 0.0f;
	LaserTime = 0.0f;
	PatternStartTime = 0.0f;
}
void Belial::IdleUpdate(float _Delta)
{
	PatternStartTime += _Delta;

	if (PatternStartTime >= 5.0f)
	{
		//Pattern = Random.RandomInt(1, 3);

		//if (Pattern == 1)
		//{
		//	ChangeState(BelialState::FireBulletReady);
		//}
		//else if (Pattern == 2)
		//{
		//	ChangeState(BelialState::SummonSword);
		//}
		//else if (Pattern == 3)
		//{
		//	ChangeState(BelialState::Laser);
		//}

		ChangeState(BelialState::Laser);
	}
}

void Belial::FireBulletReadyStart()
{
	ChangeAnimationState("FireBulletReady");
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
		std::shared_ptr<BelialSword> Sword = GetLevel()->CreateActor<BelialSword>(RenderOrder::BossProjectile);
		Sword->Transform.SetLocalPosition({ (64.0f * 6) + 128.0f * SummonSwordCount, -(64.0f * 8) });
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