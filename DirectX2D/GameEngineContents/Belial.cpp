#include "PreCompile.h"
#include "Belial.h"

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

	ChangeState(BelialState::Idle);
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
}
void Belial::IdleUpdate(float _Delta)
{
	PatternStartTime += _Delta;

	if (PatternStartTime >= 2.0f)
	{

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
}
void Belial::FireBulletUpdate(float _Delta)
{
	FireBulletTime += _Delta;

	if (FireBulletTime >= 3.0f)
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
}

void Belial::LaserStart()
{

}
void Belial::LaserUpdate(float _Delta)
{

}