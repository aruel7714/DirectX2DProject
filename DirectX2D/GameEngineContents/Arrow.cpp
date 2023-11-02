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
	GameEngineSprite::CreateSingle("CrossbowArrow.png");

	ArrowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::WeaponProjectile);
	ArrowRenderer->SetSprite("CrossbowArrow.png");

	float4 Scale = GameEngineTexture::Find("CrossbowArrow.png")->GetScale() * 4.0f;
	ArrowRenderer->SetImageScale(Scale);

	float4 PlayerScale = Player::MainPlayer->GetRendererScale();
	float4 PlayerPosition = Player::MainPlayer->Transform.GetWorldPosition();
	
	PlayerPosition.Y += (PlayerScale.Y / 5.0f);

	
	
	Transform.SetLocalPosition(PlayerPosition);

	//if (Player::MainPlayer->GetPlayerDir() == PlayerDir::Left)
	//{
	//	Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	//}
	//if (Player::MainPlayer->GetPlayerDir() == PlayerDir::Right)
	//{
	//	Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	//}

	if (Player::MainPlayer->GetPlayerDir() == PlayerDir::Right)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, (90.0f + MouseDeg) });
	}
	if (Player::MainPlayer->GetPlayerDir() == PlayerDir::Left)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -(90.0f - MouseDeg) });
	}
	
}
void Arrow::Update(float _Delta)
{
	Transform.AddLocalPosition(MouseDir * _Delta * 1500.0f);

	if (GetLiveTime() > 0.4f)
	{
		Death();
	}
}