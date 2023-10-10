#include "PreCompile.h"
#include "Level1F.h"
#include "Level1F_Floor1.h"
#include "Player.h"

Level1F::Level1F()
{
}

Level1F::~Level1F()
{
}

void Level1F::Start()
{
	if (nullptr == GameEngineSprite::Find("Starf1F"))
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

	GameEngineSprite::CreateSingle("Start1F.png");
	GameEngineSprite::CreateSingle("Start1F_Debug.png");

	Level1F_Floor = CreateActor<Level1F_Floor1>(RenderOrder::Floor);

	std::shared_ptr<class Player> MainPlayer = CreateActor<Player>(RenderOrder::Player);
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