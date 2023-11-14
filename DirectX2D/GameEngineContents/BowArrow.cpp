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

	GameEngineSprite::CreateSingle("Arrow00.png");

	ArrowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::WeaponProjectile);
	ArrowRenderer->SetSprite("Arrow00.png");
	ArrowRenderer->CreateAnimation("BowArrow", "Arrow00.png", 0.1f, -1, -1, false);
	ArrowRenderer->CreateAnimation("ArrowDisappear", "ArrowFX", 0.05f, -1, -1, false);

	ArrowRenderer->ChangeAnimation("ArrowFire");

	float4 Scale = GameEngineTexture::Find("Arrow00.png")->GetScale() * 4.0f;
	ArrowRenderer->SetImageScale(Scale);
}

void BowArrow::Update(float _Delta)
{

}