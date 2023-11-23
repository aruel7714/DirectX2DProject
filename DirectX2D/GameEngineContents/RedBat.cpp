#include "PreCompile.h"
#include "RedBat.h"

RedBat::RedBat()
{
}

RedBat::~RedBat()
{
}

void RedBat::Start()
{
	if (nullptr == GameEngineSprite::Find("RedBatIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\RedBat\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	RedBatRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);

	{
		RedBatRenderer->CreateAnimation("RedBat_Idle", "RedBatIdle");
		RedBatRenderer->CreateAnimation("RedBat_Attack", "RedBatAttack", 0.1f, -1, -1, false);
	}

	{
		//Status
		// Hp = 16.0f;
		// Damage = 5.0f;
	}
	//IdleToAttackTime > 2.5f ?
}

void RedBat::Update(float _Delta)
{

}