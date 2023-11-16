#include "PreCompile.h"
#include "BelialRightHandLaserBody.h"

BelialRightHandLaserBody::BelialRightHandLaserBody()
{
}

BelialRightHandLaserBody::~BelialRightHandLaserBody()
{
}

void BelialRightHandLaserBody::Start()
{
	if (nullptr == GameEngineSprite::Find("BelialPatternLaserHead"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialPatternLaser\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	RightLaserBodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);

	{
		RightLaserBodyRenderer->CreateAnimation("BelialRightLaserBody_Attack", "BelialPatternLaserHead", 0.1f, 0, 2, true);
		RightLaserBodyRenderer->CreateAnimation("BelialRightLaserBody_End", "BelialPatternLaserHead", 0.1f, 3, 6, false);
	}

	RightLaserBodyRenderer->SetSprite("BelialPatternLaserHead");
	float4 Scale = RightLaserBodyRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RightLaserBodyRenderer->SetImageScale(Scale);

	RightLaserBodyRenderer->LeftFlip();
}
void BelialRightHandLaserBody::Update(float _Delta)
{

}