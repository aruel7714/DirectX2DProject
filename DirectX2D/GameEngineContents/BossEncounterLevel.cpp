#include "PreCompile.h"
#include "BossEncounterLevel.h"
#include "BossEncounterFloor.h"
#include "BeforeBossEncounterLevel.h"
#include "Player.h"
#include "DungeonMoveTrigger.h"
#include "BossSpawnTrigger.h"

#include "Belial.h"
#include "BelialLeftHand.h"
#include "BelialRightHand.h"

BossEncounterLevel::BossEncounterLevel()
{
}

BossEncounterLevel::~BossEncounterLevel()
{
}

void BossEncounterLevel::Start()
{
	BossResourceLoad();
	GameEngineSprite::CreateSingle("BossRoom.png");
	GameEngineSprite::CreateSingle("BossRoom_Debug.png");

	BossEncounterFloor = CreateActor<class BossEncounterFloor>(RenderOrder::Floor);

	MainPlayer = CreateActor<Player>(RenderOrder::Player);
	MainPlayer->Transform.SetLocalPosition({ 360.0f , -1088.0f });

	std::shared_ptr<GameMouseCursor> Mouse = CreateActor<GameMouseCursor>(RenderOrder::Mouse);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BossRoom.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	BossBelial = CreateActor<Belial>(RenderOrder::BossBody);
	BossBelial->Transform.SetLocalPosition({ (64.0f * 11.0f), -((64.0f * 11.0f) + 32.0f) });

	//std::shared_ptr<BelialLeftHand> BossBelialLeftHand = CreateActor<BelialLeftHand>(RenderOrder::Monster);
	//BossBelialLeftHand->Transform.SetLocalPosition({ (64.0f * 4.0f) + 32.0f , -(MapScale.Y - (64.0f * 7.0f) - 32.0f)});

	//std::shared_ptr<BelialRightHand> BossBelialRightHand = CreateActor<BelialRightHand>(RenderOrder::Monster);
	//BossBelialRightHand->Transform.SetLocalPosition({ MapScale.X - (64.0f * 4.0f) - 32.0f, -(MapScale.Y - (64.0f * 10.0f) - 32.0f) });

	Stele1 = CreateActor<DungeonStele>(RenderOrder::DungeonBuilding);
	Stele1->Transform.SetLocalPosition({ 64.0f + 32.0f, -(MapScale.Y - 192.0f - 128.0f) });
	Stele1->Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	Stele1->SetCollisionScale({ 64.0f, 256.0f });

	Stele2 = CreateActor<DungeonStele>(RenderOrder::DungeonBuilding);
	Stele2->Transform.SetLocalPosition({ (MapScale.X - 64.0f - 32.0f), -(MapScale.Y - 192.0f - 128.0f) });
	Stele2->Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	Stele2->SetCollisionScale({ 64.0f, 256.0f });

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 192.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}

	{
		TriggerRight = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerRight->SetMoveTriggerPosition({ MapScale.X - 16.0f, -(MapScale.Y - 192.0f - 128.0f) });
		TriggerRight->SetMoveTriggerScale({ 64.0f, 256.0f });
	}

	SpawnTrigger = CreateActor<BossSpawnTrigger>(RenderOrder::DungeonBuilding);
	SpawnTrigger->SetMoveTriggerPosition({ MapScale.X / 2.0f,  -(MapScale.Y - 192.0f - 480.0f) });
	SpawnTrigger->SetMoveTriggerScale({ 64.0f, 960.0f });
}

void BossEncounterLevel::Update(float _Delta)
{
	if (SpawnTrigger->BossSpawnTriggerCollision != nullptr)
	{
		if (true == SpawnTrigger->BossSpawnTriggerCollision->IsDeath())
		{
			BossBelial->BelialMulColorPlus(_Delta);
		} 
	}

	if (true == BossBelial->IsBelialDeathState())
	{
		Stele1->SteleOpened();
		Stele2->SteleOpened();
	}

	EventParameter ParameterLeft;
	ParameterLeft.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		FadeIn->On();
		if (FadeIn->IsUpdate())
		{
			if (1.0f <= FadeIn->GetMulColorA())
			{
				GameEngineCore::ChangeLevel("BeforeBossEncounterLevel");
			}
		}
	};

	EventParameter ParameterRight;
	ParameterRight.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		FadeIn->On();
		if (FadeIn->IsUpdate())
		{
			if (1.0f <= FadeIn->GetMulColorA())
			{
				GameEngineCore::ChangeLevel("AfterBossEncounterLevel");
			}
		}
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterLeft);
	TriggerRight->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterRight);
}

void BossEncounterLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	//PrevLevel = _PrevLevel;
	//_PrevLevel->

	BossEncounterFloor->SetDebugBackGround();
	//MainPlayer->Transform.SetLocalPosition({ 180.0f , -1088.0f });

	FadeOut = CreateActor<LevelFadeOut>(RenderOrder::Fade);

	FadeIn = CreateActor<LevelFadeIn>(RenderOrder::Fade);
	FadeIn->Off();


	if (FindLevel("BeforeBossEncounterLevel") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , -1088.0f });
	}

	if (FindLevel("AfterBossEncounterLevel") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 1408.0f - 96.0f, -1088.0f });
	}
}
void BossEncounterLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	FadeIn->Death();
	//NextLevel = _NextLevel;
}

void BossEncounterLevel::BossResourceLoad()
{
	if (nullptr == GameEngineSprite::Find("BelialBackground"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("BelialBodyIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialBody\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("BelialBulletNormal"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialBullet\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("BelialLeftHandIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialLeftHand\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("BelialPatternSwordSwordBody"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialPatternSword\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("BelialPatternLaserHead"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialPatternLaser\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
}