#include "PreCompile.h"
#include "Arrow.h"
#include "Player.h"

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

void Arrow::Start()
{
	if (nullptr == GameEngineSprite::Find("CrossbowArrow.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Weapon\\");

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

	GameEngineSprite::CreateSingle("CrossbowArrow.png");

	ArrowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::WeaponProjectile);
	ArrowRenderer->SetSprite("CrossbowArrow.png");
	ArrowRenderer->CreateAnimation("ArrowFire", "CrossbowArrow.png", 0.1f, -1, -1, false);
	ArrowRenderer->CreateAnimation("ArrowDisappear", "ArrowFX", 0.05f, -1, -1, false);

	ArrowRenderer->ChangeAnimation("ArrowFire");

	float4 Scale = GameEngineTexture::Find("CrossbowArrow.png")->GetScale() * 4.0f;
	ArrowRenderer->SetImageScale(Scale);

	float4 PlayerScale = Player::MainPlayer->GetRendererScale();
	float4 PlayerPosition = Player::MainPlayer->Transform.GetWorldPosition();
	
	PlayerPosition.Y += (PlayerScale.Y / 5.0f);
	PlayerPosition.Y += 8.0f;

	if (Player::MainPlayer->GetPlayerDir() == PlayerDir::Right)
	{
		PlayerPosition.X += PlayerScale.X / 6.0f;
		Transform.SetLocalRotation({ 0.0f, 0.0f, (90.0f + MouseDeg) });
	}
	if (Player::MainPlayer->GetPlayerDir() == PlayerDir::Left)
	{
		PlayerPosition.X -= PlayerScale.X / 6.0f;
		Transform.SetLocalRotation({ 0.0f, 0.0f, -(90.0f - MouseDeg) });
	}
	
	Transform.SetLocalPosition(PlayerPosition);

	//if (Player::MainPlayer->GetPlayerDir() == PlayerDir::Left)
	//{
	//	Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	//}
	//if (Player::MainPlayer->GetPlayerDir() == PlayerDir::Right)
	//{
	//	Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	//}

	{
		ArrowCollision = CreateComponent<GameEngineCollision>(CollisionType::Weapon);
		ArrowCollision->SetCollisionType(ColType::AABBBOX2D);
		ArrowCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
		ArrowCollision->Transform.SetLocalScale({ Scale.X, Scale.X, 1.0f });
	}
	
	
	Dir = MouseDir;
	
}
void Arrow::Update(float _Delta)
{
	if (GetLiveTime() < 0.4f && ArrowRenderer->IsCurAnimation("ArrowFire"))
	{
		Transform.AddLocalPosition(Dir * _Delta * ArrowSpeed);
	}
	else if (GetLiveTime() >= 0.4f && ArrowRenderer->IsCurAnimation("ArrowFire"))
	{
		if (ArrowRenderer->IsCurAnimation("ArrowFire") && ArrowRenderer->IsCurAnimationEnd())
		{
			ArrowDisappear();
		}
	}

	EventParameter DisappearEvent;
	DisappearEvent.Stay = [&](class GameEngineCollision* _this, class GameEngineCollision* _Other)
		{
			ArrowDisappear();
		};
	ArrowCollision->CollisionEvent(CollisionType::Monster, DisappearEvent);
	

	if (ArrowRenderer->IsCurAnimation("ArrowDisappear") && ArrowRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}

void Arrow::ArrowDisappear()
{
	ArrowRenderer->SetPivotValue({ 0.5f, 0.8f });
	ArrowCollision->Death();
	ArrowRenderer->ChangeAnimation("ArrowDisappear");
	ArrowRenderer->SetImageScale(ArrowRenderer->GetCurSprite().Texture->GetScale() * 4.0f);
	Transform.SetLocalRotation({ 0.0f, 0.0f, Transform.GetLocalRotationEuler().Z + 180.0f });
}