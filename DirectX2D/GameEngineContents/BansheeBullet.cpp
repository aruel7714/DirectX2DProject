#include "PreCompile.h"
#include "BansheeBullet.h"

BansheeBullet::BansheeBullet()
{
}

BansheeBullet::~BansheeBullet()
{
}

void BansheeBullet::Start()
{
	if (nullptr == GameEngineSprite::Find("BansheeBulletIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\BansheeBullet\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterProjectile);

	{
		BulletRenderer->CreateAnimation("BansheeBullet_Idle", "BansheeBulletIdle");
		BulletRenderer->CreateAnimation("BansheeBullet_Hit", "BansheeBulletHit", 0.1f, -1, -1, false);
	}

	BulletRenderer->SetSprite("BansheeBulletIdle");

	float4 Scale = BulletRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BulletRenderer->SetImageScale(Scale);

	BulletRenderer->ChangeAnimation("BansheeBullet_Idle");
}

void BansheeBullet::Update(float _Delta)
{
	Transform.AddLocalPosition(Dir * _Delta * BulletSpeed);
}

void BansheeBullet::SetDir(int _num)
{
	switch (_num)
	{
	case 0:
		Dir = float4::RIGHT;
		break;
	case 1:
		Dir = float4::RIGHT + float4::UP;
		Dir.Normalize();
		break;
	case 2:
		Dir = float4::UP;
		break;
	case 3:
		Dir = float4::LEFT + float4::UP;
		Dir.Normalize();
		break;
	case 4:
		Dir = float4::LEFT;
		break;
	case 5:
		Dir = float4::LEFT + float4::DOWN;
		Dir.Normalize();
		break;
	case 6:
		Dir = float4::DOWN;
		break;
	case 7:
		Dir = float4::RIGHT + float4::DOWN;
		Dir.Normalize();
		break;
	default:
		break;
	}
}