#include "PreCompile.h"
#include "TitleLevel.h"
#include "ContentsEnum.h"
#include "BackCloud.h"
#include "FrontCloud.h"
#include "MainLogo.h"

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
		GameEngineSprite::CreateSingle("MainLogo2.png");
	}

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		std::shared_ptr<BackCloud> BackObject = CreateActor<BackCloud>(ContentsObjectType::BackCloud);
		std::shared_ptr<FrontCloud> FrontObject = CreateActor<FrontCloud>(ContentsObjectType::FrontCloud);
		std::shared_ptr<MainLogo> LogoObject = CreateActor<MainLogo>(ContentsObjectType::MainLogo);
	}
}
void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress('P'))
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