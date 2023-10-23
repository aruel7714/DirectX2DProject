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

	ShopFloor = CreateActor<class Level1F_Shop_Floor>(RenderOrderDungeon::Floor);
	
	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("1F_Shop.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<DungeonBuildingShop> BuildingShopRenderer = CreateActor<DungeonBuildingShop>(RenderOrderDungeon::Building);
	std::shared_ptr<DungeonNPCGiant> GiantRenderer = CreateActor<DungeonNPCGiant>(RenderOrderDungeon::NPC);

	BuildingShopRenderer->SetBuildingPosition({ 928.0f, -(MapScale.Y - 192.0f) });
	GiantRenderer->SetGiantPosition({ 1120.0f, -(MapScale.Y - 192.0f) });

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrderDungeon::Building);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 320.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
}
void Level1F_Shop::Update(float _Delta)
{
	EventParameter Parameter;
	Parameter.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F");
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, Parameter);
}

void Level1F_Shop::LevelStart(GameEngineLevel* _PrevLevel)
{
	ShopFloor->SetDebugBackGround();
	if (FindLevel("Level1F") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , -512.0f });
	}
}
void Level1F_Shop::LevelEnd(GameEngineLevel* _NextLevel)
{

}