#include "PreCompile.h"
#include "Level1F_Shop.h"
#include "Level1F_Shop_Floor.h"
#include "Player.h"
#include "DungeonNPCGiant.h"
#include "DungeonBuildingShop.h"

Level1F_Shop::Level1F_Shop()
{
}

Level1F_Shop::~Level1F_Shop()
{
}

void Level1F_Shop::Start()
{
	GameEngineSprite::CreateSingle("1F_Shop.png");
	GameEngineSprite::CreateSingle("1F_Shop_Debug.png");

	ShopFloor = CreateActor<class Level1F_Shop_Floor>(RenderOrder::Floor);
	
	MainPlayer = CreateActor<Player>(RenderOrder::Player);

	std::shared_ptr<GameMouseCursor> Mouse = CreateActor<GameMouseCursor>(RenderOrder::Mouse);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("1F_Shop.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<DungeonBuildingShop> BuildingShopRenderer = CreateActor<DungeonBuildingShop>(RenderOrder::DungeonBuilding);
	std::shared_ptr<DungeonNPCGiant> GiantRenderer = CreateActor<DungeonNPCGiant>(RenderOrder::NPC);

	BuildingShopRenderer->SetBuildingPosition({ 928.0f, -(MapScale.Y - 192.0f) });
	GiantRenderer->SetGiantPosition({ 1120.0f, -(MapScale.Y - 192.0f) });

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 320.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}

	{
		TriggerRight = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerRight->SetMoveTriggerPosition({ MapScale.X - 16.0f, -(MapScale.Y - 320.0f - 128.0f) });
		TriggerRight->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
}
void Level1F_Shop::Update(float _Delta)
{
	EventParameter ParameterLeft;
	ParameterLeft.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F_2");
	};

	EventParameter ParameterRight;
	ParameterRight.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F_3");
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterLeft);
	TriggerRight->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterRight);
}

void Level1F_Shop::LevelStart(GameEngineLevel* _PrevLevel)
{
	ShopFloor->SetDebugBackGround();

	if (FindLevel("Level1F_2") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , -512.0f });
	}

	if (FindLevel("Level1F_3") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ TriggerRight->MoveTriggerCollision->Transform.GetLocalPosition().X - 96.0f , -512.0f });
	}
}
void Level1F_Shop::LevelEnd(GameEngineLevel* _NextLevel)
{

}