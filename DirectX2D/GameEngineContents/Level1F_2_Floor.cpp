#include "PreCompile.h"
#include "Level1F_2_Floor.h"

Level1F_2_Floor::Level1F_2_Floor()
{
}

Level1F_2_Floor::~Level1F_2_Floor()
{
}

void Level1F_2_Floor::Start()
{
	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	FloorRenderer->SetSprite("Level1F_2.png");

	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	DebugFloorRenderer->SetSprite("Level1F_2_Debug.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_2.png");
	float4 ImageScale = Texture->GetScale() * 4.0f;

	FloorRenderer->SetImageScale(ImageScale);
	DebugFloorRenderer->SetImageScale(ImageScale);

	float4 ImageHalfScale = ImageScale.Half();
	ImageHalfScale.Y *= -1.0f;
	Transform.SetLocalPosition(ImageHalfScale);
}
void Level1F_2_Floor::Update(float _Delta)
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

void Level1F_2_Floor::SetDebugBackGround()
{
	DebugBackGround = this;
}