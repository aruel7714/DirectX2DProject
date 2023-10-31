#include "PreCompile.h"
#include "Level1F_1.h"
#include "Level1F_1_Floor.h"
#include "BigWhiteSkel.h"

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

	std::shared_ptr<BigWhiteSkel> MonsterBigWhiteSkel = CreateActor<BigWhiteSkel>(RenderOrder::Monster);
	MonsterBigWhiteSkel->Transform.SetLocalPosition({ 992.0f, -576.0f });
	
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