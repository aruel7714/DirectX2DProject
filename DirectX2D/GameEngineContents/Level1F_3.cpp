#include "PreCompile.h"
#include "Level1F_3.h"
#include "Level1F_3_Floor.h"

Level1F_3::Level1F_3()
{
}

Level1F_3::~Level1F_3()
{
}

void Level1F_3::Start()
{
	GameEngineSprite::CreateSingle("Level1F_3.png");
	GameEngineSprite::CreateSingle("Level1F_3_Debug.png");

	Floor3 = CreateActor<class Level1F_3_Floor>(RenderOrderDungeon::Floor);

	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_3.png");
	float4 MapScale = Texture->GetScale() * 4.0f;
}
void Level1F_3::Update(float _Delta)
{

}

void Level1F_3::LevelStart(GameEngineLevel* _PrevLevel)
{
	Floor3->SetDebugBackGround();
}
void Level1F_3::LevelEnd(GameEngineLevel* _NextLevel)
{

}