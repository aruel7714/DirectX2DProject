#include "PreCompile.h"
#include "SkelDog.h"

SkelDog::SkelDog()
{
}

SkelDog::~SkelDog()
{
}

void SkelDog::Start()
{
	if (nullptr == GameEngineSprite::Find("BigWhiteSkelIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\SkelDog\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	SkelDogRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);

	{
		SkelDogRenderer->CreateAnimation("SkelDog_Idle", "SkelDogIdle");
		SkelDogRenderer->CreateAnimation("SkelDog_Move", "SkelDogRun");
		SkelDogRenderer->CreateAnimation("SkelDog_AttackReady", "SkelDogIdle", 0.1f, -1, -1, false);
		SkelDogRenderer->CreateAnimation("SkelDog_Attack", "SkelDogMove", 0.1f, -1, -1, false);
	}
}

void SkelDog::Update(float _Delta)
{

}