#include "PreCompile.h"
#include "TownFloor.h"

TownFloor* TownFloor::DebugFloor;

TownFloor::TownFloor()
{
	DebugFloor = this;
}

TownFloor::~TownFloor()
{
}

void TownFloor::Start()
{
	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	FloorRenderer->SetSprite("Town.png");

	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	//DebugFloorRenderer->SetSprite("Town_DebugRed.png");
	DebugFloorRenderer->SetSprite("Town_DebugAll.png");
	
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Town.png");

	float4 ImageScale = Texture->GetScale() * 4;

	//FloorRenderer->SetSamplerState(SamplerOption::POINT);
	FloorRenderer->SetImageScale(ImageScale);

	//DebugFloorRenderer->SetSamplerState(SamplerOption::POINT);
	DebugFloorRenderer->SetImageScale(ImageScale);

	float4 ImageHalfScale = ImageScale.Half();
	ImageHalfScale.Y *= -1.0f;
	Transform.SetLocalPosition(ImageHalfScale);

	//float4 HScale = Texture->GetScale().Half();
	//FloorRenderer->SetImageScale(Transform.GetLocalScale() * 4);
	
	//HScale.Y *= -1.0f;

	//float4 Scale = FloorRenderer->Transform.GetLocalScale();
	//Scale *= 4.0f;
	//Transform.SetLocalScale(Scale);

	//Transform.SetLocalPosition(HScale);

	//FloorRenderer->On();

	//DebugBackGround = this;

	GameEngineInput::AddInputObject(this);
}

void TownFloor::Update(float _Delta)
{
	/*if (GameEngineInput::IsUp('P'))
	{
		SwitchRenderer();
	}*/

	float4 FloorPos = Transform.GetWorldPosition();
	int a = 0;

	if (GameEngineInput::IsDown(VK_F2, this))
	{
		IsDebug = !IsDebug;
	}

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

void TownFloor::SetDebugMode()
{
	IsDebug = !IsDebug;
}

//GameEngineColor TownFloor::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
//{
//	// 플레이어의 위치를 이미지의 좌표계로 변경한다.
//	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다.
//	_Pos.Y *= -1.0f;
//
//	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Town_DebugRed.png");
//
//
//	return Tex->GetColor(_Pos / 4.0f, _DefaultColor);
//}

//void TownFloor::SwitchRenderer()
//{
//	SwitchRenderValue = !SwitchRenderValue;
//
//	if (true == SwitchRenderValue)
//	{
//		FloorRenderer->On();
//		DebugFloorRenderer->Off();
//	}
//	else
//	{
//		FloorRenderer->Off();
//		DebugFloorRenderer->On();
//	}
//}

void TownFloor::SetDebugBackGround()
{
	DebugBackGround = this;
}