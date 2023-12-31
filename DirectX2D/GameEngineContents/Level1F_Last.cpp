#include "PreCompile.h"
#include "Level1F_Last.h"
#include "Level1F_Last_Floor.h"
#include "DownDoor.h"

Level1F_Last::Level1F_Last()
{
}

Level1F_Last::~Level1F_Last()
{
}

void Level1F_Last::Start()
{
	GameEngineSprite::CreateSingle("Level1F_Last.png");
	GameEngineSprite::CreateSingle("Level1F_Last_Debug.png");

	FloorLast = CreateActor<class Level1F_Last_Floor>(RenderOrder::Floor);

	MainPlayer = CreateActor<Player>(RenderOrder::Player);

	std::shared_ptr<GameMouseCursor> Mouse = CreateActor<GameMouseCursor>(RenderOrder::Mouse);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_Last.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<DownDoor> Door = CreateActor<DownDoor>(RenderOrder::NPC);
	Door->SetDoorPosition({ (MapScale.X / 2.0f) - 2.0f, -(MapScale.Y - 128.0f) });

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 128.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
}
void Level1F_Last::Update(float _Delta)
{
	EventParameter ParameterLeft;
	ParameterLeft.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		FadeIn->On();
		if (FadeIn->IsUpdate())
		{
			if (1.0f <= FadeIn->GetMulColorA())
			{
				GameEngineCore::ChangeLevel("Level1F_3");
			}
		}
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterLeft);

	if (true == MainPlayer->GetIsDownValue())
	{
		FadeIn->On();
		if (FadeIn->IsUpdate())
		{
			if (1.0f <= FadeIn->GetMulColorA())
			{
				GlobalSound::Bgm.Stop();
				GameEngineCore::ChangeLevel("BeforeBossEncounterLevel");
				MainPlayer->IsDownFalse();
			}
		}
	}
}

void Level1F_Last::LevelStart(GameEngineLevel* _PrevLevel)
{
	FloorLast->SetDebugBackGround();

	FadeOut = CreateActor<LevelFadeOut>(RenderOrder::Fade);

	FadeIn = CreateActor<LevelFadeIn>(RenderOrder::Fade);
	FadeIn->Off();

	if (FindLevel("Level1F_3") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , TriggerLeft->MoveTriggerCollision->Transform.GetLocalPosition().Y - 128.0f });
	}
}
void Level1F_Last::LevelEnd(GameEngineLevel* _NextLevel)
{
	FadeIn->Death();
}