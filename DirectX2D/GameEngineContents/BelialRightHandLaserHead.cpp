#include "PreCompile.h"
#include "BelialRightHandLaserHead.h"

BelialRightHandLaserHead::BelialRightHandLaserHead()
{
}

BelialRightHandLaserHead::~BelialRightHandLaserHead()
{
}

void BelialRightHandLaserHead::Start()
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

	RightLaserHeadRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);

	{
		RightLaserHeadRenderer->CreateAnimation("BelialRightLaserHead_Attack", "BelialPatternLaserHead", 0.1f, 0, 2, true);
		RightLaserHeadRenderer->CreateAnimation("BelialRightLaserHead_End", "BelialPatternLaserHead", 0.1f, 3, 6, false);
	}

	RightLaserHeadRenderer->SetSprite("BelialPatternLaserHead");
	float4 Scale = RightLaserHeadRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RightLaserHeadRenderer->SetImageScale(Scale);

	RightLaserHeadRenderer->LeftFlip();
}
void BelialRightHandLaserHead::Update(float _Delta)
{

}