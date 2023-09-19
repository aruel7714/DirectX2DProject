#include "PreCompile.h"
#include "TownSecondFloorRight.h"

TownSecondFloorRight::TownSecondFloorRight()
{
}

TownSecondFloorRight::~TownSecondFloorRight()
{
}

void TownSecondFloorRight::Start() 
{
	SecondFloorRightRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::SecondFloor);
	SecondFloorRightRenderer->SetSprite("SecondFloor3_32.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("SecondFloor3_32.png");

	SecondFloorRightRenderer->SetPivotType(PivotType::Bottom);

	float4 ImageScale = Texture->GetScale() * 4.0f;

	SecondFloorRightRenderer->SetSamplerState(SamplerOption::POINT);
	SecondFloorRightRenderer->SetImageScale(ImageScale);

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4;

	Transform.SetLocalPosition({ MapScale.X - ((Texture->GetScale().X) + 158.0f) , -(MapScale.Y - 192.0f) });
}
void TownSecondFloorRight::Update(float _Delta)
{
}