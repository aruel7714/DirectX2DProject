#include "PreCompile.h"
#include "TownFloor.h"

TownFloor::TownFloor()
{
}

TownFloor::~TownFloor()
{
}

void TownFloor::Start()
{
	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	FloorRenderer->SetSprite("Town.png");
	
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Town.png");

	FloorRenderer->SetSamplerState(SamplerOption::POINT);
	

	float4 HScale = Texture->GetScale().Half();
	//FloorRenderer->SetImageScale(Transform.GetLocalScale() * 4);
	
	HScale.Y *= -1.0f;

	float4 Scale = FloorRenderer->Transform.GetLocalScale();
	Scale *= 4.0f;
	Transform.SetLocalScale(Scale);

	Transform.SetLocalPosition(HScale);

	//FloorRenderer->On();
}

void TownFloor::Update(float _Delta)
{
	/*if (GameEngineInput::IsUp('P'))
	{
		SwitchRenderer();
	}*/

	float4 FloorPos = Transform.GetWorldPosition();
	int a = 0;
}

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