#include "PreCompile.h"
#include "Level1F_3.h"
#include "Level1F_3_Floor.h"

#include "BigWhiteSkel.h"
#include "RustyGreatSwordSkel.h"
#include "RustyShortSwordSkel.h"
#include "Minotaurs.h"

#include "DungeonStele.h"
#include "DungeonTorch.h"

Level1F_3::Level1F_3()
{
}

Level1F_3::~Level1F_3()
{
}

void Level1F_3::Start()
{
	GameEngineSprite::CreateSingle("Level1F_3.png");
	GameEngineSprite::CreateSingle("Level1F_3_Debug.png");

	Floor3 = CreateActor<class Level1F_3_Floor>(RenderOrder::Floor);

	MainPlayer = CreateActor<Player>(RenderOrder::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_3.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<BigWhiteSkel> MonsterBigWhiteSkel = CreateActor<BigWhiteSkel>(RenderOrder::Monster);
	MonsterBigWhiteSkel->Transform.SetLocalPosition({ 640.0f, -512.0f });

	std::shared_ptr<RustyGreatSwordSkel> MonsterRustyGreatSwordSkel = CreateActor< RustyGreatSwordSkel>(RenderOrder::Monster);
	MonsterRustyGreatSwordSkel->Transform.SetLocalPosition({ 768.0f, -512.0f });

	//1280
	std::shared_ptr<Minotaurs> MonsterMinotaurs = CreateActor<Minotaurs>(RenderOrder::Monster);
	MonsterMinotaurs->Transform.SetLocalPosition({ 640.0f, -1280.0f });
	
	std::shared_ptr<RustyShortSwordSkel> MonsterRustyShortSwordSkel = CreateActor< RustyShortSwordSkel>(RenderOrder::Monster);
	MonsterRustyShortSwordSkel->Transform.SetLocalPosition({ 448.0f, -2048.0f });

	std::shared_ptr<DungeonTorch> Torch1 = CreateActor<DungeonTorch>(RenderOrder::DungeonProp);
	Torch1->Transform.SetLocalPosition({ 1152.0f, -992.0f });

	std::shared_ptr<DungeonTorch> Torch2 = CreateActor<DungeonTorch>(RenderOrder::DungeonProp);
	Torch2->Transform.SetLocalPosition({ 224.0f, -1792.0f });

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 128.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}

	{
		TriggerRight = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerRight->SetMoveTriggerPosition({ MapScale.X - 16.0f, -(512.0f - 128.0f) });
		TriggerRight->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
}
void Level1F_3::Update(float _Delta)
{
	EventParameter ParameterLeft;
	ParameterLeft.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F_Shop");
	};

	EventParameter ParameterRight;
	ParameterRight.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F_Last");
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterLeft);
	TriggerRight->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterRight);
}

void Level1F_3::LevelStart(GameEngineLevel* _PrevLevel)
{
	Floor3->SetDebugBackGround();

	if (FindLevel("Level1F_Shop") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , TriggerLeft->MoveTriggerCollision->Transform.GetLocalPosition().Y - 128.0f });
	}

	if (FindLevel("Level1F_Last") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ TriggerRight->MoveTriggerCollision->Transform.GetLocalPosition().X - 96.0f , -576.0f });
	}
}
void Level1F_3::LevelEnd(GameEngineLevel* _NextLevel)
{

}