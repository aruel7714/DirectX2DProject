#include "PreCompile.h"
#include "Level1F.h"
#include "Level1F_Floor1.h"
#include "FloorDoor.h"
#include "Player.h"

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
		Dir.MoveChild("ContentsResources\\Texture\\Stage1F\\Floor1F");
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
		Dir.MoveChild("ContentsResources\\Texture\\Stage1F\\Prop");
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

	std::shared_ptr<class Player> MainPlayer = CreateActor<Player>(RenderOrder::Player);

	std::shared_ptr<class FloorDoor> Door = CreateActor<FloorDoor>(RenderOrder::Building);
}
void Level1F::Update(float _Delta)
{

}

void Level1F::LevelStart(GameEngineLevel* _PrevLevel)
{
	Level1F_Floor->SetDebugBackGround();
}
void Level1F::LevelEnd(GameEngineLevel* _NextLevel)
{

}