#include "PreCompile.h"
#include "Level1F_2.h"
#include "Level1F_2_Floor.h"

#include "Banshee.h"
#include "RustyShortSwordSkel.h"
#include "SkelDog.h"

Level1F_2::Level1F_2()
{
}

Level1F_2::~Level1F_2()
{
}

void Level1F_2::Start()
{
	GameEngineSprite::CreateSingle("Level1F_2.png");
	GameEngineSprite::CreateSingle("Level1F_2_Debug.png");

	Floor2 = CreateActor<class Level1F_2_Floor>(RenderOrder::Floor);

	MainPlayer = CreateActor<Player>(RenderOrder::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_2.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<Banshee> MonsterBanshee = CreateActor<Banshee>(RenderOrder::Monster);
	MonsterBanshee->Transform.SetLocalPosition({ 1344.0f, -256.0f });

	std::shared_ptr<RustyShortSwordSkel> MonsterRustyShortSwordSkel = CreateActor<RustyShortSwordSkel>(RenderOrder::Monster);
	MonsterRustyShortSwordSkel->Transform.SetLocalPosition({ 1920.0f, -448.0f });

	std::shared_ptr<SkelDog> MonsterSkelDog = CreateActor<SkelDog>(RenderOrder::Monster);
	MonsterSkelDog->Transform.SetLocalPosition({ 1088.0f, -640.0f });

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 128.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}

	{
		TriggerRight = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerRight->SetMoveTriggerPosition({ MapScale.X - 16.0f, -(MapScale.Y - 384.0f - 128.0f) });
		TriggerRight->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
}
void Level1F_2::Update(float _Delta)
{
	EventParameter ParameterLeft;
	ParameterLeft.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F");
	};

	EventParameter ParameterRight;
	ParameterRight.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F_Shop");
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterLeft);
	TriggerRight->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterRight);
}

void Level1F_2::LevelStart(GameEngineLevel* _PrevLevel)
{
	Floor2->SetDebugBackGround();

	if (FindLevel("Level1F") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , -1088.0f });
	}

	if (FindLevel("Level1F_Shop") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ TriggerRight->MoveTriggerCollision->Transform.GetLocalPosition().X - 96.0f , -832.0f });
	}
}
void Level1F_2::LevelEnd(GameEngineLevel* _NextLevel)
{

}