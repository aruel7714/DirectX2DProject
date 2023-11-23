#include "PreCompile.h"
#include "BlueBat.h"

BlueBat::BlueBat()
{
}

BlueBat::~BlueBat()
{
}

void BlueBat::Start()
{
	if (nullptr == GameEngineSprite::Find("BlueBatIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\BlueBat\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	BlueBatRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	
	{
		BlueBatRenderer->CreateAnimation("BlueBat_Move", "BlueBatIdle");
	}

	{
		// Status
		Hp = 6.0f;
		// Not Attack
	}
}

void BlueBat::Update(float _Delta)
{

}