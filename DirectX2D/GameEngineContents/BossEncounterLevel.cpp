#include "PreCompile.h"
#include "BossEncounterLevel.h"
#include "BossEncounterFloor.h"
#include "BeforeBossEncounterLevel.h"
#include "Player.h"
#include "DungeonMoveTrigger.h"

BossEncounterLevel::BossEncounterLevel()
{
}

BossEncounterLevel::~BossEncounterLevel()
{
}

void BossEncounterLevel::Start()
{
	
	GameEngineSprite::CreateSingle("BossRoom.png");
	GameEngineSprite::CreateSingle("BossRoom_Debug.png");

	BossEncounterFloor = CreateActor<class BossEncounterFloor>(RenderOrderDungeon::Floor);

	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);
	MainPlayer->Transform.SetLocalPosition({ 360.0f , -1088.0f });

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BossRoom.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrderDungeon::Building);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 128.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
}

void BossEncounterLevel::Update(float _Delta)
{
	EventParameter Parameter;
	Parameter.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("BeforeBossEncounterLevel");
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, Parameter);
}

void BossEncounterLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	//PrevLevel = _PrevLevel;
	//_PrevLevel->

	BossEncounterFloor->SetDebugBackGround();
	//MainPlayer->Transform.SetLocalPosition({ 180.0f , -1088.0f });


	if (NextLevel == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , -1088.0f });
	}
}
void BossEncounterLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	//NextLevel = _NextLevel;
}