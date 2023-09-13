#include "PreCompile.h"
#include "TownLevel.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "TownSky.h"
#include "TownFloor.h"

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
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}
		}

		GameEngineSprite::CreateSingle("Sky_Day2.png");
		//GameEngineSprite::CreateSingle("TownBG_Day.png");
		//GameEngineSprite::CreateSingle("TownLayer_Day.png");
		GameEngineSprite::CreateSingle("Town.png");
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		std::shared_ptr<TownSky> TownBackSky = CreateActor<TownSky>(RenderOrder::BackGround);

		std::shared_ptr<TownFloor> _TownFloor = CreateActor<TownFloor>(RenderOrder::Floor);
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