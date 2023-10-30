#include "PreCompile.h"
#include "Level1F_Inn_Floor.h"

Level1F_Inn_Floor::Level1F_Inn_Floor()
{
}

Level1F_Inn_Floor::~Level1F_Inn_Floor()
{
}

void Level1F_Inn_Floor::Start()
{
	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	FloorRenderer->SetSprite("1F_Inn.png");

	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	DebugFloorRenderer->SetSprite("1F_Inn_Debug.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("1F_Inn.png");
	float4 ImageScale = Texture->GetScale() * 4.0f;

	FloorRenderer->SetImageScale(ImageScale);
	DebugFloorRenderer->SetImageScale(ImageScale);

	float4 ImageHalfScale = ImageScale.Half();
	ImageHalfScale.Y *= -1.0f;
	Transform.SetLocalPosition(ImageHalfScale);
}

void Level1F_Inn_Floor::Update(float _Delta)
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

void Level1F_Inn_Floor::SetDebugBackGround()
{
	DebugBackGround = this;
}