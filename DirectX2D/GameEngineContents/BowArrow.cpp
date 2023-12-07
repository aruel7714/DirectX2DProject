#include "PreCompile.h"
#include "BowArrow.h"

BowArrow::BowArrow()
{
}

BowArrow::~BowArrow()
{
}

void BowArrow::Start()
{
	if (nullptr == GameEngineSprite::Find("Arrow00.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\Skel\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("ArrowFX"))
	{

		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\WeaponFX\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	GameEngineSprite::CreateSingle("Arrow00.png");

	ArrowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::WeaponProjectile);
	ArrowRenderer->SetSprite("Arrow00.png");
	ArrowRenderer->CreateAnimation("BowArrow", "Arrow00.png", 0.1f, -1, -1, false);
	ArrowRenderer->CreateAnimation("ArrowDisappear", "ArrowFX", 0.05f, -1, -1, false);

	ArrowRenderer->ChangeAnimation("BowArrow");

	float4 Scale = GameEngineTexture::Find("Arrow00.png")->GetScale() * 4.0f;
	ArrowRenderer->SetImageScale(Scale);

	{
		ArrowCollision = CreateComponent<GameEngineCollision>(CollisionType::MonsterAttack);
		ArrowCollision->SetCollisionType(ColType::AABBBOX2D);
		ArrowCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
		ArrowCollision->Transform.SetLocalScale({ Scale.X, Scale.X, 1.0f });
	}
}

void BowArrow::Update(float _Delta)
{
	if (Dir.X < 0)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, Deg + 90.0f });
	}
	else
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, Deg - 90.0f });
	}
	
	if (GetLiveTime() < 0.4f && ArrowRenderer->IsCurAnimation("BowArrow"))
	{
		Transform.AddLocalPosition(Dir * _Delta * ArrowSpeed);
	}
	else if (GetLiveTime() >= 0.4f && ArrowRenderer->IsCurAnimation("BowArrow"))
	{
		if (ArrowRenderer->IsCurAnimation("BowArrow") && ArrowRenderer->IsCurAnimationEnd())
		{
			ArrowDisappear();
		}
	}

	EventParameter DisappearEvent;
	DisappearEvent.Stay = [&](class GameEngineCollision* _this, class GameEngineCollision* _Other)
		{
			ArrowDisappear();
		};
	ArrowCollision->CollisionEvent(CollisionType::Player, DisappearEvent);

	if (ArrowRenderer->IsCurAnimation("ArrowDisappear") && ArrowRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}

void BowArrow::ArrowDisappear()
{
	ArrowRenderer->SetPivotValue({ 0.5f, 0.8f });
	ArrowCollision->Death();
	ArrowRenderer->ChangeAnimation("ArrowDisappear");
	ArrowRenderer->SetImageScale(ArrowRenderer->GetCurSprite().Texture->GetScale() * 4.0f);
	Transform.SetLocalRotation({ 0.0f, 0.0f, Transform.GetLocalRotationEuler().Z + 180.0f });
}