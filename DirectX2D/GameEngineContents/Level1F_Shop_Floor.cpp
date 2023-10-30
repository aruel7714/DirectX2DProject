#include "PreCompile.h"
#include "Level1F_Shop_Floor.h"

Level1F_Shop_Floor::Level1F_Shop_Floor()
{
}

Level1F_Shop_Floor::~Level1F_Shop_Floor()
{
}

void Level1F_Shop_Floor::Start()
{
	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	FloorRenderer->SetSprite("1F_Shop.png");

	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	DebugFloorRenderer->SetSprite("1F_Shop_Debug.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("1F_Shop.png");
	float4 ImageScale = Texture->GetScale() * 4.0f;

	FloorRenderer->SetImageScale(ImageScale);
	DebugFloorRenderer->SetImageScale(ImageScale);

	float4 ImageHalfScale = ImageScale.Half();
	ImageHalfScale.Y *= -1.0f;
	Transform.SetLocalPosition(ImageHalfScale);
}
void Level1F_Shop_Floor::Update(float _Delta)
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

void Level1F_Shop_Floor::SetDebugBackGround()
{
	DebugBackGround = this;
}