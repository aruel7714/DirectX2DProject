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

	AfterBossEncounterFloor = CreateActor<class AfterBossEncounterFloor>(RenderOrder::Floor);

	MainPlayer = CreateActor<Player>(RenderOrder::Player);
	
	std::shared_ptr<GameMouseCursor> Mouse = CreateActor<GameMouseCursor>(RenderOrder::Mouse);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("AfterBossEncounter.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<DownDoor> Door = CreateActor<DownDoor>(RenderOrder::NPC);
	Door->SetDoorPosition({ 638.0f, -(MapScale.Y - 256.0f) });

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrder::Building);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 256.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
}
void AfterBossEncounterLevel::Update(float _Delta)
{
	EventParameter Parameter;
	Parameter.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		FadeIn->On();
		if (FadeIn->IsUpdate())
		{
			if (1.0f <= FadeIn->GetMulColorA())
			{
				GameEngineCore::ChangeLevel("BossEncounterLevel");
			}
		}
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, Parameter);
	
	if (true == MainPlayer->GetIsDownValue())
	{
		FadeIn->On();
		if (FadeIn->IsUpdate())
		{
			if (1.0f <= FadeIn->GetMulColorA())
			{
				GameEngineCore::ChangeLevel("EndingLevel");
				MainPlayer->IsDownFalse();
			}
		}
	}
}

void AfterBossEncounterLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	AfterBossEncounterFloor->SetDebugBackGround();

	FadeOut = CreateActor<LevelFadeOut>(RenderOrder::Fade);

	FadeIn = CreateActor<LevelFadeIn>(RenderOrder::Fade);
	FadeIn->Off();

	if (FindLevel("BossEncounterLevel") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , -512.0f });
	}
}
void AfterBossEncounterLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	FadeIn->Death();
}