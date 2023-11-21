#include "PreCompile.h"
#include "Level1F_1.h"
#include "Level1F_1_Floor.h"
#include "BigWhiteSkel.h"
#include "RustyGreatSwordSkel.h"
#include "ArcherSkel.h"
#include "LittleGhost.h"
#include "Banshee.h"

Level1F_1::Level1F_1()
{
}

Level1F_1::~Level1F_1()
{
}

void Level1F_1::Start()
{
	GameEngineSprite::CreateSingle("Level1F_1.png");
	GameEngineSprite::CreateSingle("Level1F_1_Debug.png");

	Floor1 = CreateActor<class Level1F_1_Floor>(RenderOrder::Floor);

	MainPlayer = CreateActor<Player>(RenderOrder::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_1.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<BigWhiteSkel> MonsterBigWhiteSkel1 = CreateActor<BigWhiteSkel>(RenderOrder::Monster);
	MonsterBigWhiteSkel1->Transform.SetLocalPosition({ 992.0f, -576.0f });

	std::shared_ptr<BigWhiteSkel> MonsterBigWhiteSkel2 = CreateActor<BigWhiteSkel>(RenderOrder::Monster);
	MonsterBigWhiteSkel2->Transform.SetLocalPosition({ 1504.0f, -576.0f });

	std::shared_ptr<RustyGreatSwordSkel> MonsterRustyGreatSwordSkel = CreateActor< RustyGreatSwordSkel>(RenderOrder::Monster);
	MonsterRustyGreatSwordSkel->Transform.SetLocalPosition({ 1248.0f, -576.0f });

	std::shared_ptr<ArcherSkel> MonsterArcherSkel1 = CreateActor<ArcherSkel>(RenderOrder::Monster);
	MonsterArcherSkel1->Transform.SetLocalPosition({ 1024.0f, -896.0f });

	std::shared_ptr<ArcherSkel> MonsterArcherSkel2 = CreateActor<ArcherSkel>(RenderOrder::Monster);
	MonsterArcherSkel2->Transform.SetLocalPosition({ 1472.0f, -896.0f });

	std::shared_ptr<LittleGhost> MonsterLittleGhost1 = CreateActor<LittleGhost>(RenderOrder::Monster);
	MonsterLittleGhost1->Transform.SetLocalPosition({ 992.0f, -384.0f });

	std::shared_ptr<LittleGhost> MonsterLittleGhost2 = CreateActor<LittleGhost>(RenderOrder::Monster);
	MonsterLittleGhost2->Transform.SetLocalPosition({ 1120.0f, -384.0f });

	std::shared_ptr<LittleGhost> MonsterLittleGhost3 = CreateActor<LittleGhost>(RenderOrder::Monster);
	MonsterLittleGhost3->Transform.SetLocalPosition({ 1376.0f, -384.0f });

	std::shared_ptr<LittleGhost> MonsterLittleGhost4 = CreateActor<LittleGhost>(RenderOrder::Monster);
	MonsterLittleGhost4->Transform.SetLocalPosition({ 1504.0f, -384.0f });

	std::shared_ptr<Banshee> MonsterBanshee = CreateActor<Banshee>(RenderOrder::Monster);
	MonsterBanshee->Transform.SetLocalPosition({ 1248.0f, -256.0f });

	//std::shared_ptr<DungeonStele> Stele1 = CreateActor<DungeonStele>(RenderOrder::DungeonBuilding);
	//Stele1->Transform.SetLocalPosition({ 64.0f + 32.0f, -(576.0f - 128.0f) });
	//Stele1->Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	//Stele1->SetCollisionScale({ 64.0f, 256.0f });

	//std::shared_ptr<DungeonStele> Stele2 = CreateActor<DungeonStele>(RenderOrder::DungeonBuilding);
	//Stele2->Transform.SetLocalPosition({ (MapScale.X - 64.0f - 32.0f), -(576.0f - 128.0f) });
	//Stele2->Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	//Stele2->SetCollisionScale({ 64.0f, 256.0f });
	
	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(576.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}

	{
		TriggerRight = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerRight->SetMoveTriggerPosition({ MapScale.X - 16.0f, -(576.0f - 128.0f) });
		TriggerRight->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
}
void Level1F_1::Update(float _Delta)
{
	EventParameter ParameterLeft;
	ParameterLeft.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F_Inn");
	};

	EventParameter ParameterRight;
	ParameterRight.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F");
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterLeft);
	TriggerRight->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterRight);

}

void Level1F_1::LevelStart(GameEngineLevel* _PrevLevel)
{
	Floor1->SetDebugBackGround();

	if (FindLevel("Level1F_Inn") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , -576.0f });
	}

	if (FindLevel("Level1F") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ TriggerRight->MoveTriggerCollision->Transform.GetLocalPosition().X - 96.0f , -576.0f });
	}

}
void Level1F_1::LevelEnd(GameEngineLevel* _NextLevel)
{

}