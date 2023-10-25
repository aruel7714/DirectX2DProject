#include "PreCompile.h"
#include "Level1F_3.h"
#include "Level1F_3_Floor.h"

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

	Floor3 = CreateActor<class Level1F_3_Floor>(RenderOrderDungeon::Floor);

	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_3.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrderDungeon::Building);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 128.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}

	{
		TriggerRight = CreateActor<DungeonMoveTrigger>(RenderOrderDungeon::Building);
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