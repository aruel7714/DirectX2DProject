#include "PreCompile.h"
#include "Level1F.h"
#include "Level1F_Floor1.h"
#include "FloorDoor.h"
#include "Player.h"

#include "BelialRightHand.h"
#include "BelialLeftHand.h"
#include "BelialSword.h"
#include "BelialBullet.h"
#include "RedBat.h"

#include "DungeonTorch.h"
#include "GargoyleStatue.h"

#include <GameEngineCore/FadePostEffect.h>

Level1F::Level1F()
{
}

Level1F::~Level1F()
{
}

void Level1F::Start()
{
	if (nullptr == GameEngineSprite::Find("Start1F.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Dungeon\\Stage1F\\Floor1F");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("Door0.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Dungeon\\Prop");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Dungeon\\DungeonBuilding");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Dungeon\\NPC\\");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\FX\\");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++) 
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	GameEngineSprite::CreateSingle("Start1F.png");
	GameEngineSprite::CreateSingle("Start1F_Debug.png");

	Level1F_Floor = CreateActor<Level1F_Floor1>(RenderOrder::Floor);

	MainPlayer = CreateActor<Player>(RenderOrder::Player);

	MainPlayer->Transform.SetLocalPosition({ 515.0f , -640.0f });

	std::shared_ptr<GameMouseCursor> Mouse = CreateActor<GameMouseCursor>(RenderOrder::Mouse);

	std::shared_ptr<class FloorDoor> Door = CreateActor<FloorDoor>(RenderOrder::DungeonProp);
	
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Start1F.png");
	float4 MapScale = Texture->GetScale() * 4.0f;
	Door->SetDoorPosition({ 515.0f, -(MapScale.Y - 128.0f) });

	std::shared_ptr<DungeonTorch> Torch = CreateActor<DungeonTorch>(RenderOrder::DungeonProp);
	Torch->Transform.SetLocalPosition({ 1216.0f, -448.0f });

	std::shared_ptr<GargoyleStatue> Statue1 = CreateActor<GargoyleStatue>(RenderOrder::DungeonProp);
	Statue1->Transform.SetLocalPosition({ 1056.0f, -640.0f });

	std::shared_ptr<GargoyleStatue> Statue2 = CreateActor<GargoyleStatue>(RenderOrder::DungeonProp);
	Statue2->Transform.SetLocalPosition({ 1376.0f, -640.0f });

	//std::shared_ptr<BelialBullet> Bullet = CreateActor<BelialBullet>(RenderOrder::Monster);
	////MonsterRustyGreatSwordSkel->Transform.SetLocalPosition({ 1215.0f , -640.0f });
	//Bullet->Transform.SetLocalPosition({ 1215.0f , -540.0f });

	/*std::shared_ptr<RedBat> MonsterSkelDog = CreateActor<RedBat>(RenderOrder::Monster);
	MonsterSkelDog->Transform.SetLocalPosition({ 1215.0f , -500.0f });*/
	

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 128.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}

	{
		TriggerRight = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerRight->SetMoveTriggerPosition({ MapScale.X - 16.0f, -(MapScale.Y - 128.0f - 128.0f) });
		TriggerRight->SetMoveTriggerScale({ 64.0f ,256.0f });
	}
}
void Level1F::Update(float _Delta)
{
	EventParameter ParameterLeft;
	ParameterLeft.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		FadeIn->On();
		if (FadeIn->IsUpdate())
		{
			if (1.0f <= FadeIn->GetMulColorA())
			{
				GameEngineCore::ChangeLevel("Level1F_1");
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
				GameEngineCore::ChangeLevel("Level1F_2");
			}
		}
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterLeft);
	TriggerRight->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterRight);
}

void Level1F::LevelStart(GameEngineLevel* _PrevLevel)
{
	Level1F_Floor->SetDebugBackGround();
	//MainPlayer->Transform.SetLocalPosition({ 515.0f , -640.0f });

	GlobalSound::Bgm = GameEngineSound::SoundPlay("1.JailField.wav");

	FadeOut = CreateActor<LevelFadeOut>(RenderOrder::Fade);

	FadeIn = CreateActor<LevelFadeIn>(RenderOrder::Fade);
	FadeIn->Off();

	if (FindLevel("Level1F_1") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , -640.0f });
	}

	if (FindLevel("Level1F_2") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ TriggerRight->MoveTriggerCollision->Transform.GetLocalPosition().X - 96.0f , -640.0f });
	}
}
void Level1F::LevelEnd(GameEngineLevel* _NextLevel)
{
	FadeIn->Death();
}