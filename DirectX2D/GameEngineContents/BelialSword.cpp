#include "PreCompile.h"
#include "BelialSword.h"

BelialSword::BelialSword()
{
}

BelialSword::~BelialSword()
{
}

void BelialSword::Start()
{
	if (nullptr == GameEngineSprite::Find("BelialPatternSwordSwordBody"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialPatternSword\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	GameEngineSprite::CreateSingle("BossSword.png");

	{
		SwordChargeRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectileEffect);
		SwordChargeRenderer->CreateAnimation("SwordChargeFX", "BelialPatternSwordCharge");
		SwordChargeRenderer->ChangeAnimation("SwordChargeFX");
		float4 Scale = SwordChargeRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
		SwordChargeRenderer->SetImageScale(Scale);
	}

	SwordRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);
	SwordRenderer->SetSprite("BossSword.png");
	float4 Scale = SwordChargeRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	SwordRenderer->SetImageScale(Scale);
}
void BelialSword::Update(float _Delta)
{


}