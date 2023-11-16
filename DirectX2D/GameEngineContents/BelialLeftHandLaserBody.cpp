#include "PreCompile.h"
#include "BelialLeftHandLaserBody.h"

BelialLeftHandLaserBody::BelialLeftHandLaserBody()
{
}

BelialLeftHandLaserBody::~BelialLeftHandLaserBody()
{
}

void BelialLeftHandLaserBody::Start()
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

	LeftLaserBodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);

	{
		LeftLaserBodyRenderer->CreateAnimation("BelialLeftLaserBody_Attack", "BelialPatternLaserBody", 0.1f, 0, 2, true);
		LeftLaserBodyRenderer->CreateAnimation("BelialLeftLaserBody_End", "BelialPatternLaserBody", 0.1f, 3, 6, false);
	}

	LeftLaserBodyRenderer->SetSprite("BelialPatternLaserBody");
	float4 Scale = LeftLaserBodyRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LeftLaserBodyRenderer->SetImageScale(Scale);
}
void BelialLeftHandLaserBody::Update(float _Delta)
{

}