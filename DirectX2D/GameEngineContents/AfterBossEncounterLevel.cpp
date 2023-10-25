#include "PreCompile.h"
#include "AfterBossEncounterLevel.h"
#include "AfterBossEncounterFloor.h"
#include "Player.h"
#include "DungeonMoveTrigger.h"
#include "DownDoor.h"

AfterBossEncounterLevel::AfterBossEncounterLevel()
{
}

AfterBossEncounterLevel::~AfterBossEncounterLevel()
{
}

void AfterBossEncounterLevel::Start()
{
	GameEngineSprite::CreateSingle("AfterBossEncounter.png");
	GameEngineSprite::CreateSingle("AfterBossEncounter_Debug.png");

	AfterBossEncounterFloor = CreateActor<class AfterBossEncounterFloor>(RenderOrderDungeon::Floor);

	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("AfterBossEncounter.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<DownDoor> Door = CreateActor<DownDoor>(RenderOrderDungeon::NPC);
	Door->SetDoorPosition({ 638.0f, -(MapScale.Y - 256.0f) });

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrderDungeon::Building);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 256.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
}
void AfterBossEncounterLevel::Update(float _Delta)
{
	EventParameter Parameter;
	Parameter.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("BossEncounterLevel");
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, Parameter);
	
}

void AfterBossEncounterLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	AfterBossEncounterFloor->SetDebugBackGround();

	if (FindLevel("BossEncounterLevel") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , -512.0f });
	}
}
void AfterBossEncounterLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}