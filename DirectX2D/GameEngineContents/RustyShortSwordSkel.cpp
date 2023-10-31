#include "PreCompile.h"
#include "RustyShortSwordSkel.h"

RustyShortSwordSkel::RustyShortSwordSkel()
{
}

RustyShortSwordSkel::~RustyShortSwordSkel()
{
}

void RustyShortSwordSkel::Start()
{
	if (nullptr == GameEngineSprite::Find("RustyShortSword"))
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

	RustyShortSwordSkelRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	RustyShortSwordRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterWeapon);

	{
		RustyShortSwordSkelRenderer->CreateAnimation("RustyShortSwordSkel_Idle", "SkelIdle");
		RustyShortSwordSkelRenderer->CreateAnimation("RustyShortSwordSkel_Move", "SkelWalk");
		RustyShortSwordSkelRenderer->CreateAnimation("RustyShortSwordSkel_Attack", "SkelAttack");
		RustyShortSwordSkelRenderer->CreateAnimation("RustyShortSwordSkel_AttackReady", "SkelAttack");
	}
	{
		RustyShortSwordRenderer->CreateAnimation("RustyShortSword_Attack", "RustyShortSword");
		RustyShortSwordRenderer->CreateAnimation("RustyShortSword_AttackReady", "RustyShortSword", 0, 0);
	}


}
void RustyShortSwordSkel::Update(float _Delta)
{

}