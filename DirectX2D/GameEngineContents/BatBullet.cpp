#include "PreCompile.h"
#include "BatBullet.h"

BatBullet::BatBullet()
{
}

BatBullet::~BatBullet()
{
}

void BatBullet::Start()
{
	if (nullptr == GameEngineSprite::Find("RangeBallBullet"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\BatBullet\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterProjectile);

	{
		BulletRenderer->CreateAnimation("BatBullet_Normal", "RangeBallBullet");
		BulletRenderer->CreateAnimation("BatBullet_Hit", "RangeBallBulletHit", 0.1f, -1, -1, false);
	}

	BulletRenderer->SetSprite("RangeBallBullet");
	float4 Scale = BulletRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BulletRenderer->SetImageScale(Scale);

	ChangeState(BulletState::Normal);

	{
		BulletCollision = CreateComponent<GameEngineCollision>(CollisionType::MonsterAttack);
		BulletCollision->SetCollisionType(ColType::SPHERE2D);
		BulletCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
		BulletCollision->Transform.SetLocalScale(Scale);
	}
}
void BatBullet::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BatBullet::ChangeState(BulletState _State)
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
void BatBullet::StateUpdate(float _Delta)
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
void BatBullet::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BatBullet_";
	AnimationName += _State;
	BulletRenderer->ChangeAnimation(AnimationName);
}

void BatBullet::NormalStart()
{
	ChangeAnimationState("Normal");
}
void BatBullet::NormalUpdate(float _Delta)
{


	EventParameter HitParameter;
	HitParameter.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ChangeState(BulletState::Hit);
		};

	BulletCollision->CollisionEvent(CollisionType::Player, HitParameter);

	float4 Position = Transform.GetLocalPosition();
	if (Position.X <= 0.0f ||
		Position.X >= 352.0f * 4.0f ||
		Position.Y >= 0.0f ||
		Position.Y <= -(320.0f * 4.0f))
	{
		ChangeState(BulletState::Hit);
	}
}

void BatBullet::HitStart()
{
	ChangeAnimationState("Hit");
}
void BatBullet::HitUpdate(float _Delta)
{
	if (BulletRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}