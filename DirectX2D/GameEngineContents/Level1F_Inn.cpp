#include "PreCompile.h"
#include "Level1F_Inn.h"
#include "Level1F_Inn_Floor.h"
#include "Player.h"
#include "DungeonNPCInn.h"
#include "DungeonBuildingInn.h"

Level1F_Inn::Level1F_Inn()
{
}

Level1F_Inn::~Level1F_Inn()
{
}

void Level1F_Inn::Start()
{
	GameEngineSprite::CreateSingle("1F_Inn.png");
	GameEngineSprite::CreateSingle("1F_Inn_Debug.png");

	InnFloor = CreateActor<class Level1F_Inn_Floor>(RenderOrderDungeon::Floor);

	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("1F_Inn.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<DungeonBuildingInn> BuildingInnRenderer = CreateActor<DungeonBuildingInn>(RenderOrderDungeon::Building);
	std::shared_ptr<DungeonNPCInn> InnRenderer = CreateActor<DungeonNPCInn>(RenderOrderDungeon::NPC);

	BuildingInnRenderer->SetBuildingPosition({ 768.0f, -(MapScale.Y - 192.0f) });
	InnRenderer->SetInnPosition({ 1024.0f, -(MapScale.Y - 192.0f) });

	{
		TriggerRight = CreateActor<DungeonMoveTrigger>(RenderOrderDungeon::Building);
		TriggerRight->SetMoveTriggerPosition({ MapScale.X - 16.0f, -(MapScale.Y - 320.0f - 128.0f) });
		TriggerRight->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
	
}
void Level1F_Inn::Update(float _Delta)
{
	EventParameter Parameter;
	Parameter.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F");
	};

	TriggerRight->MoveTriggerCollision->CollisionEvent(CollisionType::Player, Parameter);
}

void Level1F_Inn::LevelStart(GameEngineLevel* _PrevLevel)
{
	InnFloor->SetDebugBackGround();

	if (FindLevel("Level1F") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ TriggerRight->MoveTriggerCollision->Transform.GetLocalPosition().X - 96.0f , -512.0f });
	}
}
void Level1F_Inn::LevelEnd(GameEngineLevel* _NextLevel)
{

}