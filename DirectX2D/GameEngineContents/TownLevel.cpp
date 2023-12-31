#include "PreCompile.h"
#include "TownLevel.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "TownSky.h"
#include "TownFloor.h"
#include "DebugFloor.h"
#include "TestMap.h"
#include "TownSecondFloorLeft.h"
#include "TownSecondFloorMiddle.h"
#include "TownSecondFloorRight.h"
#include "TownBuilding.h"

//NPC
#include "TownNPCBlackSmith.h"
#include "TownNPCMerchant.h"
#include "TownNPCCommander.h"
#include "TownNPCBoutique.h"
#include "TownNPCPistolMan.h"
#include "TownNPCTemple.h"
#include "TownNPCBuilder.h"
#include "TownDungeonIngurgitate.h"
#include "TownDungeonEat.h"

//Trigger
#include "TownDungeonTrigger.h"

//Weapon
#include "ShortSword.h"

TownLevel::TownLevel()
{
}

TownLevel::~TownLevel()
{
}

void TownLevel::Start()
{
	{
		if (nullptr == GameEngineSprite::Find("Sky_Day2.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources\\Texture\\Town\\TownSky");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}
		}

		if (nullptr == GameEngineSprite::Find("Town.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources\\Texture\\Town\\TownFloor");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}
		}

		if (nullptr == GameEngineSprite::Find("SecondFloor3_32.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources\\Texture\\Town\\TownSecondFloor");
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
			Dir.MoveChild("ContentsResources\\Texture\\Town\\TownBuilding");
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
			Dir.MoveChild("ContentsResources\\Texture\\Town\\TownBG");
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
			Dir.MoveChild("ContentsResources\\Texture\\Town\\TownFG");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}
		}

		{
			// NPC

			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources\\Texture\\Town\\TownNPC\\");
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
			Dir.MoveChild("ContentsResources\\Texture\\UI\\Keyboard");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}
		}

		GameEngineSprite::CreateSingle("Sky_Day2.png");
		GameEngineSprite::CreateSingle("TownBG_Day.png");
		GameEngineSprite::CreateSingle("TownLayer_Day.png");
		GameEngineSprite::CreateSingle("Town.png");
		GameEngineSprite::CreateSingle("Town_Debug.png");
		GameEngineSprite::CreateSingle("Town_DebugAll.png");
		GameEngineSprite::CreateSingle("Town_DebugRed.png");
		GameEngineSprite::CreateSingle("Test.png");
		GameEngineSprite::CreateSingle("SecondFloor3_32.png");
		GameEngineSprite::CreateSingle("SecondFloor2_32.png");

		// Building
		GameEngineSprite::CreateSingle("TrainingSchool.png");
		GameEngineSprite::CreateSingle("Shop.png");
		GameEngineSprite::CreateSingle("BlackSmith.png");
		GameEngineSprite::CreateSingle("Boutique.png");
		GameEngineSprite::CreateSingle("Gunsmith.png");
		GameEngineSprite::CreateSingle("Temple.png");
		GameEngineSprite::CreateSingle("TempleFront.png");
		GameEngineSprite::CreateSingle("BuildingOffice.png");

		// BuildingProp
		GameEngineSprite::CreateSingle("BlackSmithDisplay.png");
		GameEngineSprite::CreateSingle("Target.png");
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		std::shared_ptr<TownSky> TownBackSky = CreateActor<TownSky>(RenderOrder::BackGround);

		_TownFloor = CreateActor<TownFloor>(RenderOrder::Floor);

		//std::shared_ptr<DebugFloor> DebugTownFloor = CreateActor<DebugFloor>(RenderOrder::Debug);

		//std::shared_ptr<TestMap> TestMapFloor = CreateActor<TestMap>(RenderOrder::Floor);

		std::shared_ptr<TownSecondFloorLeft> LeftSecondFloor = CreateActor<TownSecondFloorLeft>(RenderOrder::SecondFloor);
		std::shared_ptr<TownSecondFloorRight> RightSecondFloor = CreateActor<TownSecondFloorRight>(RenderOrder::SecondFloor);
		std::shared_ptr<TownSecondFloorMiddle> MiddleSecondFloor = CreateActor<TownSecondFloorMiddle>(RenderOrder::SecondFloor);

		std::shared_ptr<TownBuilding> TownBuildings = CreateActor<TownBuilding>(RenderOrder::Building);


	}

	{
		//NPC
		std::shared_ptr<TownNPCBlackSmith> Haken = CreateActor<TownNPCBlackSmith>(RenderOrder::NPC);
		std::shared_ptr<TownNPCMerchant> Millia = CreateActor<TownNPCMerchant>(RenderOrder::NPC);
		std::shared_ptr<TownNPCCommander> Coblovina = CreateActor<TownNPCCommander>(RenderOrder::NPC);
		std::shared_ptr<TownNPCBoutique> Bloch = CreateActor<TownNPCBoutique>(RenderOrder::NPC);
		std::shared_ptr<TownNPCPistolMan> Fiat = CreateActor<TownNPCPistolMan>(RenderOrder::NPC);
		std::shared_ptr<TownNPCTemple> Rozen = CreateActor<TownNPCTemple>(RenderOrder::NPC);
		std::shared_ptr<TownNPCBuilder> Yulford = CreateActor<TownNPCBuilder>(RenderOrder::NPC);
	}

	{
		//Trigger
		Trigger = CreateActor<TownDungeonTrigger>(RenderOrder::Building);
	}

	std::shared_ptr<GameMouseCursor> Mouse = CreateActor<GameMouseCursor>(RenderOrder::Mouse);

	MainPlayer = CreateActor<Player>(RenderOrder::Player);
	//std::shared_ptr<ShortSword> WeaponShortSword = CreateActor<ShortSword>(RenderOrder::Weapon);
}

void TownLevel::Update(float _Delta)
{

	if (Count == 0)
	{
		if (Trigger->DungeonTriggerCollision->IsDeath())
		{
			DungeonEat = CreateActor<TownDungeonEat>(RenderOrder::NPC);
			//DungeonIngurgitate->Transform.SetLocalPosition(MainPlayer->Transform.GetLocalPosition());
			float4 Pos = MainPlayer->Transform.GetLocalPosition();
			DungeonEat->Transform.SetLocalPosition({ Pos.X, Trigger->DungeonTriggerCollision->Transform.GetLocalPosition().Y + 32.0f});
			MainPlayer->ChangeStateStay();
			Count++;
		}
	}

	if (nullptr != DungeonEat)
	{
		if (DungeonEat->EatRenderer->IsCurAnimation("DungeonEat_Spawn"))
		{
			if (DungeonEat->EatRenderer->IsCurAnimationEnd())
			{
				MainPlayer->WeaponOff();
				MainPlayer->Off();
			}
		}
		else if (DungeonEat->EatRenderer->IsCurAnimation("DungeonEat_Down"))
		{
			if (DungeonEat->EatRenderer->IsCurAnimationEnd())
			{ 
				FadeIn->On();
			}
		}
		
	}

	if (true == FadeIn->IsUpdate())
	{
		if (1.0f <= FadeIn->GetMulColorA())
		{
			GlobalSound::Bgm.Stop();
			GameEngineCore::ChangeLevel("Level1F");
		}
	}
}

void TownLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer->Transform.SetWorldPosition({ 3700.0f, -890.0f, -500.0f, 1.0f });

	_TownFloor->SetDebugBackGround();

	GlobalSound::Bgm = GameEngineSound::SoundPlay("0.Town.wav");

	FadeOut = CreateActor<LevelFadeOut>(RenderOrder::Fade);

	FadeIn = CreateActor<LevelFadeIn>(RenderOrder::Fade);
	FadeIn->Off();
}
void TownLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	FadeIn->Death();
	MainPlayer->On();
	MainPlayer->WeaponOn();
}