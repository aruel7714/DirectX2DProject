#include "PreCompile.h"
#include "Belial.h"

Belial::Belial()
{
}

Belial::~Belial()
{
}

void Belial::Start()
{
	if (nullptr == GameEngineSprite::Find("BelialBackGround"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	BelialBackGroundRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossBackGround);
	BelialBackGroundRenderer->CreateAnimation("BackGround", "BelialBackground");
}

void Belial::Update(float _Delta)
{

}