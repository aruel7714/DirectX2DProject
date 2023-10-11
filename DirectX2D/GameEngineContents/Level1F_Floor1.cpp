#include "PreCompile.h"
#include "Level1F_Floor1.h"

Level1F_Floor1::Level1F_Floor1()
{
}

Level1F_Floor1::~Level1F_Floor1()
{
}

void Level1F_Floor1::Start()
{
	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder1F::Floor);
	FloorRenderer->SetSprite("Start1F.png");
	
	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder1F::Floor);
	DebugFloorRenderer->SetSprite("Start1F_Debug.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Start1F.png");
	float4 ImageScale = Texture->GetScale() * 4;

	FloorRenderer->SetImageScale(ImageScale);
	DebugFloorRenderer->SetImageScale(ImageScale);

	float4 ImageHalfScale = ImageScale.Half();
	ImageHalfScale.Y *= -1.0f;
	Transform.SetLocalPosition(ImageHalfScale);

	//DebugBackGround = this;
}

void Level1F_Floor1::Update(float _Delta)
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

	if (true == GameEngineInput::IsDown(VK_F5))
	{
		IsDebug = !IsDebug;
	}
}

void Level1F_Floor1::SetDebugBackGround()
{
	DebugBackGround = this;
}