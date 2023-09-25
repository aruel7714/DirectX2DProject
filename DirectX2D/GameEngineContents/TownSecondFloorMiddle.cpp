#include "PreCompile.h"
#include "TownSecondFloorMiddle.h"

TownSecondFloorMiddle::TownSecondFloorMiddle()
{
}

TownSecondFloorMiddle::~TownSecondFloorMiddle()
{
}

void TownSecondFloorMiddle::Start() 
{
	SecondFloorMiddleRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::SecondFloor);
	SecondFloorMiddleRenderer->SetSprite("SecondFloor2_32.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("SecondFloor2_32.png");

	SecondFloorMiddleRenderer->SetPivotType(PivotType::Bottom);

	float4 ImageScale = Texture->GetScale() * 4.0f;

	//SecondFloorMiddleRenderer->SetSamplerState(SamplerOption::POINT);
	SecondFloorMiddleRenderer->SetImageScale(ImageScale);

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4;

	Transform.SetLocalPosition({ (MapScale.X / 2.0f) + 2.0f, -(MapScale.Y - 128.0f) });
}
void TownSecondFloorMiddle::Update(float _Delta)
{
}