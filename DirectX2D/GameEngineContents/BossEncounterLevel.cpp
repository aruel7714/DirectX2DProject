#include "PreCompile.h"
#include "BossEncounterLevel.h"
#include "BossEncounterFloor.h"
#include "BeforeBossEncounterLevel.h"
#include "Player.h"
#include "DungeonMoveTrigger.h"

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

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BossRoom.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<Belial> BossBelial = CreateActor<Belial>(RenderOrder::BossBody);
	BossBelial->Transform.SetLocalPosition({ (64.0f * 11.0f), -((64.0f * 11.0f) + 32.0f) });

	//std::shared_ptr<BelialLeftHand> BossBelialLeftHand = CreateActor<BelialLeftHand>(RenderOrder::Monster);
	//BossBelialLeftHand->Transform.SetLocalPosition({ (64.0f * 4.0f) + 32.0f , -(MapScale.Y - (64.0f * 7.0f) - 32.0f)});

	//std::shared_ptr<BelialRightHand> BossBelialRightHand = CreateActor<BelialRightHand>(RenderOrder::Monster);
	//BossBelialRightHand->Transform.SetLocalPosition({ MapScale.X - (64.0f * 4.0f) - 32.0f, -(MapScale.Y - (64.0f * 10.0f) - 32.0f) });


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
}

void BossEncounterLevel::Update(float _Delta)
{
	EventParameter ParameterLeft;
	ParameterLeft.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("BeforeBossEncounterLevel");
	};

	EventParameter ParameterRight;
	ParameterRight.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("AfterBossEncounterLevel");
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