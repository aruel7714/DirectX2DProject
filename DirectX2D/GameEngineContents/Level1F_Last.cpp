#include "PreCompile.h"
#include "Level1F_Last.h"
#include "Level1F_Last_Floor.h"

Level1F_Last::Level1F_Last()
{
}

Level1F_Last::~Level1F_Last()
{
}

void Level1F_Last::Start()
{
	GameEngineSprite::CreateSingle("Level1F_Last.png");
	GameEngineSprite::CreateSingle("Level1F_Last_Debug.png");

	FloorLast = CreateActor<class Level1F_Last_Floor>(RenderOrderDungeon::Floor);

	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_Last.png");
	float4 MapScale = Texture->GetScale() * 4.0f;
}
void Level1F_Last::Update(float _Delta)
{
	
}

void Level1F_Last::LevelStart(GameEngineLevel* _PrevLevel)
{
	FloorLast->SetDebugBackGround();
}
void Level1F_Last::LevelEnd(GameEngineLevel* _NextLevel)
{

}