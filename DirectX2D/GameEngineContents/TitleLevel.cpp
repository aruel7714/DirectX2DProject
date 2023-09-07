#include "PreCompile.h"
#include "TitleLevel.h"

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
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}

		GameEngineSprite::CreateSingle("BackCloud.png");
		GameEngineSprite::CreateSingle("FrontCloud.png");
		GameEngineSprite::CreateSingle("MainLogo.png");
	}

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective)
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