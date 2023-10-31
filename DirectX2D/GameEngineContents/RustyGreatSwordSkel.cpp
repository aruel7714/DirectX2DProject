#include "PreCompile.h"
#include "RustyGreatSwordSkel.h"

RustyGreatSwordSkel::RustyGreatSwordSkel()
{
}

RustyGreatSwordSkel::~RustyGreatSwordSkel()
{
}

void RustyGreatSwordSkel::Start()
{
	if (nullptr == GameEngineSprite::Find("RustyGreatSword"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\Skel\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	RustyGreatSwordSkelRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	RustyGreatSwordRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterWeapon);

	{
		RustyGreatSwordSkelRenderer->CreateAnimation("RustyGreatSwordSkel_Idle", "SkelIdle");
		RustyGreatSwordSkelRenderer->CreateAnimation("RustyGreatSwordSkel_Move", "SkelWalk");
		RustyGreatSwordSkelRenderer->CreateAnimation("RustyGreatSwordSkel_Attack", "SkelAttack");
		RustyGreatSwordSkelRenderer->CreateAnimation("RustyGreatSwordSkel_AttackReady", "SkelAttack");
	}
	{
		RustyGreatSwordRenderer->CreateAnimation("RustyGreatSword_Attack", "RustyGreatSword");
		RustyGreatSwordRenderer->CreateAnimation("RustyGreatSword_AttackReady", "RustyGreatSword", 0, 0);
	}
}
void RustyGreatSwordSkel::Update(float _Delta)
{

}