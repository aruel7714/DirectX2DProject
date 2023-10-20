#include "PreCompile.h"
#include "BeforeBossEncounterLevel.h"
#include "BeforeBossEncounterFloor.h"
#include "Player.h"
#include "FloorDoor.h"
#include "DungeonMoveTrigger.h"
#include "BossEncounterLevel.h"

BeforeBossEncounterLevel::BeforeBossEncounterLevel()
{
}

BeforeBossEncounterLevel::~BeforeBossEncounterLevel()
{
}

void BeforeBossEncounterLevel::Start()
{
	//this->SetName(std::string("BeforeBossEncounterLevel"));

	if (nullptr == GameEngineSprite::Find("BossEncounter.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Dungeon\\Stage2F\\Floor");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}

	GameEngineSprite::CreateSingle("BossEncount.png");
	GameEngineSprite::CreateSingle("BossEncount_Debug.png");

	BeforeBossEncounterFloor = CreateActor<class BeforeBossEncounterFloor>(RenderOrderDungeon::Floor);

	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);
	MainPlayer->Transform.SetLocalPosition({ 478.0f , -576.0f });

	std::shared_ptr<class FloorDoor> Door = CreateActor<FloorDoor>(RenderOrderDungeon::Prop);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BossEncount.png");
	float4 MapScale = Texture->GetScale() * 4.0f;
	Door->SetDoorPosition({ 478.0f, -(MapScale.Y - 192.0f) });

	{
		TriggerRight = CreateActor<DungeonMoveTrigger>(RenderOrderDungeon::Building);
		TriggerRight->SetMoveTriggerPosition({ MapScale.X - 16.0f, -(MapScale.Y - 192.0f - 128.0f) });
		TriggerRight->SetMoveTriggerScale({ 64.0f ,256.0f });
	}
}
void BeforeBossEncounterLevel::Update(float _Delta)
{
	EventParameter Parameter;
	Parameter.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("BossEncounterLevel");
	};

	TriggerRight->MoveTriggerCollision->CollisionEvent(CollisionType::Player, Parameter);

	//TriggerRight->CollisionEvent(CollisionType::Trigger, Parameter);
}

void BeforeBossEncounterLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = _PrevLevel;

	BeforeBossEncounterFloor->SetDebugBackGround();

	if (NextLevel == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ TriggerRight->MoveTriggerCollision->Transform.GetLocalPosition().X - 96.0f , -576.0f});
	}
}
void BeforeBossEncounterLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	//NextLevel = _NextLevel;
}