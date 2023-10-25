#include "PreCompile.h"
#include "Level1F_3_Floor.h"

Level1F_3_Floor::Level1F_3_Floor()
{
}

Level1F_3_Floor::~Level1F_3_Floor()
{
}

void Level1F_3_Floor::Start()
{
	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrderDungeon::Floor);
	FloorRenderer->SetSprite("Level1F_3.png");

	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrderDungeon::Floor);
	DebugFloorRenderer->SetSprite("Level1F_3_Debug.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_3.png");
	float4 ImageScale = Texture->GetScale() * 4.0f;

	FloorRenderer->SetImageScale(ImageScale);
	DebugFloorRenderer->SetImageScale(ImageScale);

	float4 ImageHalfScale = ImageScale.Half();
	ImageHalfScale.Y *= -1.0f;
	Transform.SetLocalPosition(ImageHalfScale);
}

void Level1F_3_Floor::Update(float _Delta)
{
	if (false == IsDebug)
	{
		FloorRenderer->On();
		DebugFloorRenderer->Off();
	}
	else
	{
		FloorRenderer->Off();
		DebugFloorRenderer->On();
	}
}

void Level1F_3_Floor::SetDebugBackGround()
{
	DebugBackGround = this;
}