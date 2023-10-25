#include "PreCompile.h"
#include "Level1F_2.h"
#include "Level1F_2_Floor.h"

Level1F_2::Level1F_2()
{
}

Level1F_2::~Level1F_2()
{
}

void Level1F_2::Start()
{
	GameEngineSprite::CreateSingle("Level1F_2.png");
	GameEngineSprite::CreateSingle("Level1F_2_Debug.png");

	Floor2 = CreateActor<class Level1F_2_Floor>(RenderOrderDungeon::Floor);

	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_2.png");
	float4 MapScale = Texture->GetScale() * 4.0f;
}
void Level1F_2::Update(float _Delta)
{

}

void Level1F_2::LevelStart(GameEngineLevel* _PrevLevel)
{
	Floor2->SetDebugBackGround();
}
void Level1F_2::LevelEnd(GameEngineLevel* _NextLevel)
{

}