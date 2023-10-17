#include "PreCompile.h"
#include "TitleLevel.h"
#include "ContentsEnum.h"
#include "BackCloud.h"
#include "FrontCloud.h"
#include "MainLogo.h"
#include "TitleBird.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Texture");
		Dir.MoveChild("TitleLevel");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("BackCloud2.png");
		GameEngineSprite::CreateSingle("FrontCloud2.png");
		//GameEngineSprite::CreateSingle("MainLogo2.png");
		GameEngineSprite::CreateSingle("MainLogo4x.png");
	}

	if (nullptr == GameEngineSprite::Find("Bird"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\TitleLevel\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	HalfWindowScale.Y *= -1.0f;

	GetMainCamera()->Transform.SetLocalPosition(HalfWindowScale);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		std::shared_ptr<BackCloud> BackObject = CreateActor<BackCloud>(TitleRenderOrder::BackCloud);
		std::shared_ptr<FrontCloud> FrontObject = CreateActor<FrontCloud>(TitleRenderOrder::FrontCloud);
		std::shared_ptr<MainLogo> LogoObject = CreateActor<MainLogo>(TitleRenderOrder::MainLogo);
		std::shared_ptr<TitleBird> BirdObject = CreateActor<TitleBird>(TitleRenderOrder::TitleBird);
	}
	GameEngineInput::AddInputObject(this);
}
void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress('P', this))
	{
		GameEngineCore::ChangeLevel("TownLevel");
	}

	if (GameEngineInput::IsPress(VK_F1, this))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}