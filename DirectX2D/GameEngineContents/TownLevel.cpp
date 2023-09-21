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
#include "TownNPCBlackSmith.h"
#include "TownNPCMerchant.h"
#include "TownNPCCommander.h"
#include "TownNPCBoutique.h"
#include "TownNPCPistolMan.h"

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
			// NPC
			{
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
		}

		

		GameEngineSprite::CreateSingle("Sky_Day2.png");
		//GameEngineSprite::CreateSingle("TownBG_Day.png");
		//GameEngineSprite::CreateSingle("TownLayer_Day.png");
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
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		std::shared_ptr<TownSky> TownBackSky = CreateActor<TownSky>(RenderOrder::BackGround);

		std::shared_ptr<TownFloor> _TownFloor = CreateActor<TownFloor>(RenderOrder::Floor);

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
	}

	std::shared_ptr<Player> MainPlayer = CreateActor<Player>(RenderOrder::Player);

}

void TownLevel::Update(float _Delta)
{
	
}

void TownLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}
void TownLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}