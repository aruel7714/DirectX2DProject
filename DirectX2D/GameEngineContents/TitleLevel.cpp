#include "PreCompile.h"
#include "TitleLevel.h"
#include "ContentsEnum.h"
#include "BackCloud.h"
#include "FrontCloud.h"
#include "MainLogo.h"
#include "TitleBird.h"
#include "TitleMouse.h"
#include "GameStartButton.h"
#include "SettingButton.h"
#include "GameExitButton.h"

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
		GameEngineSprite::CreateSingle("BlackTexture.png");
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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Sound");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineSound::SoundLoad(File.GetStringPath());
		}
	}

	GameEngineFont::Load("Perfect DOS VGA 437");

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	HalfWindowScale.Y *= -1.0f;

	GetMainCamera()->Transform.SetLocalPosition(HalfWindowScale);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		std::shared_ptr<BackCloud> BackObject = CreateActor<BackCloud>(TitleRenderOrder::BackCloud);
		std::shared_ptr<FrontCloud> FrontObject = CreateActor<FrontCloud>(TitleRenderOrder::FrontCloud);
		std::shared_ptr<MainLogo> LogoObject = CreateActor<MainLogo>(TitleRenderOrder::UI);
		std::shared_ptr<TitleBird> BirdObject = CreateActor<TitleBird>(TitleRenderOrder::TitleBird);
		std::shared_ptr<TitleMouse> MouseObject = CreateActor<TitleMouse>(TitleRenderOrder::Mouse);
	}

	GameStartButtonObject = CreateActor<GameStartButton>(TitleRenderOrder::UI);
	SettingButtonObject = CreateActor<SettingButton>(TitleRenderOrder::UI);
	GameExitButtonObject = CreateActor<GameExitButton>(TitleRenderOrder::UI);

	

}
void TitleLevel::Update(float _Delta)
{

	if (GameStartButtonObject->FadeOnOff == true)
	{
		FadeIn->On();
	}

	if (true == FadeIn->IsUpdate())
	{
		if (1.0f <= FadeIn->GetMulColorA())
		{
			GlobalSound::Bgm.Stop();
			GameEngineCore::ChangeLevel("TownLevel");
		}
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GlobalSound::Bgm = GameEngineSound::SoundPlay("title.wav");
	FadeIn = CreateActor<LevelFadeIn>(RenderOrder::Fade);
	FadeIn->Off();
	int a = 0;
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	FadeIn->Death();
	int a = 0;
}