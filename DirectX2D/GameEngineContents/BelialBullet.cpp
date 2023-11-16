#include "PreCompile.h"
#include "BelialBullet.h"

BelialBullet::BelialBullet()
{
}

BelialBullet::~BelialBullet()
{
}

void BelialBullet::Start()
{
	if (nullptr == GameEngineSprite::Find("BelialBulletNormal"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialBullet\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);
	
	{
		BulletRenderer->CreateAnimation("BelialBullet_Normal", "BelialBulletNormal");
		BulletRenderer->CreateAnimation("BelialBullet_Hit", "BelialBulletFX", 0.1f, -1, -1, false);
	}

	BulletRenderer->SetSprite("BelialBulletNormal");

	float4 Scale = BulletRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BulletRenderer->SetImageScale(Scale);

	ChangeState(BulletState::Normal);

	{
		BulletCollision = CreateComponent<GameEngineCollision>(CollisionType::MonsterAttack);
		BulletCollision->SetCollisionType(ColType::SPHERE2D);
		BulletCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
		BulletCollision->Transform.SetLocalScale({ Scale.X, Scale.Y, 1.0f });
	}
}
void BelialBullet::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BelialBullet::ChangeState(BulletState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BulletState::Normal:
			NormalStart();
			break;
		case BulletState::Hit:
			HitStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void BelialBullet::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BulletState::Normal:
		return NormalUpdate(_Delta);
	case BulletState::Hit:
		return HitUpdate(_Delta);
	default:
		break;
	}
}
void BelialBullet::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BelialBullet_";
	AnimationName += _State;
	BulletRenderer->ChangeAnimation(AnimationName);
}

void BelialBullet::NormalStart()
{
	ChangeAnimationState("Normal");
}
void BelialBullet::NormalUpdate(float _Delta)
{
	

	EventParameter HitParameter;
	HitParameter.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		ChangeState(BulletState::Hit);
	};

	BulletCollision->CollisionEvent(CollisionType::Player, HitParameter);
}

void BelialBullet::HitStart()
{
	BulletCollision->Off();
	ChangeAnimationState("Hit");
}
void BelialBullet::HitUpdate(float _Delta)
{

}