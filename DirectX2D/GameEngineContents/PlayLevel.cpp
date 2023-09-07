#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "TownSky.h"


PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	//{
	//	// ������ ���̴��� ���δ� ���δ� �ε��ϴ� �ڵ带 ģ��.
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("GameEngineResources");
	//	Dir.MoveChild("ContentsResources");
	//	Dir.MoveChild("Texture");
	//	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	//	for (size_t i = 0; i < Files.size(); i++)
	//	{
	//		// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
	//		GameEngineFile& File = Files[i];
	//		GameEngineTexture::Load(File.GetStringPath());
	//	}

	//	GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);

	//}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Texture");
		Dir.MoveChild("Town");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("Sky_Day2.png");
		GameEngineSprite::CreateSingle("TownBG_Day.png");
		GameEngineSprite::CreateSingle("TownLayer_Day.png");
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	{
		std::shared_ptr<TownSky> TownBackSky = CreateActor<TownSky>(RenderOrder::BackGround);
	}

	std::shared_ptr<Player> MainPlayer = CreateActor<Player>(RenderOrder::Player);

}

void PlayLevel::Update(float _Delta)
{
	int a = 0;
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}