#include "PreCompile.h"
#include "Level1F_1.h"
#include "Level1F_1_Floor.h"

Level1F_1::Level1F_1()
{
}

Level1F_1::~Level1F_1()
{
}

void Level1F_1::Start()
{
	GameEngineSprite::CreateSingle("Level1F_1.png");
	GameEngineSprite::CreateSingle("Level1F_1_Debug.png");

	Floor1 = CreateActor<class Level1F_1_Floor>(RenderOrderDungeon::Floor);

	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_1.png");
	float4 MapScale = Texture->GetScale() * 4.0f;
	
}
void Level1F_1::Update(float _Delta)
{

}

void Level1F_1::LevelStart(GameEngineLevel* _PrevLevel)
{
	Floor1->SetDebugBackGround();
}
void Level1F_1::LevelEnd(GameEngineLevel* _NextLevel)
{

}