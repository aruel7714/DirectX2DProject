#include "PreCompile.h"
#include "BelialLeftHandLaserHead.h"

BelialLeftHandLaserHead::BelialLeftHandLaserHead()
{
}

BelialLeftHandLaserHead::~BelialLeftHandLaserHead()
{
}

void BelialLeftHandLaserHead::Start()
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

	LeftLaserHeadRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);

	{
		LeftLaserHeadRenderer->CreateAnimation("BelialLeftLaserHead_Attack", "BelialPatternLaserHead", 0.1f, 0, 2, true);
		LeftLaserHeadRenderer->CreateAnimation("BelialLeftLaserHead_End", "BelialPatternLaserHead", 0.1f, 3, 6, false);
	}

	LeftLaserHeadRenderer->SetSprite("BelialPatternLaserHead");
	float4 Scale = LeftLaserHeadRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LeftLaserHeadRenderer->SetImageScale(Scale);
}
void BelialLeftHandLaserHead::Update(float _Delta)
{

}