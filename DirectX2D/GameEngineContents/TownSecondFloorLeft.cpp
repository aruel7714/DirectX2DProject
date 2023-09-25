#include "PreCompile.h"
#include "TownSecondFloorLeft.h"

TownSecondFloorLeft* TownSecondFloorLeft::DebugSecondFloorLeft;

TownSecondFloorLeft::TownSecondFloorLeft()
{
	DebugSecondFloorLeft;
}

TownSecondFloorLeft::~TownSecondFloorLeft()
{
}

void TownSecondFloorLeft::Start()
{
	SecondFloorLeftRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::SecondFloor);
	SecondFloorLeftRenderer->SetSprite("SecondFloor3_32.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("SecondFloor3_32.png");

	SecondFloorLeftRenderer->SetPivotType(PivotType::Bottom);

	float4 ImageScale = Texture->GetScale() * 4.0f;

	//SecondFloorLeftRenderer->SetSamplerState(SamplerOption::POINT);
	SecondFloorLeftRenderer->SetImageScale(ImageScale);

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4;

	//Transform.SetLocalPosition({ (Texture->GetScale().X) + 30.0f , -(MapScale.Y - 192.0f)});
	Transform.SetLocalPosition({ (Texture->GetScale().X) + 94.0f , -(MapScale.Y - 192.0f) });

	// Middle Position
	//Transform.SetLocalPosition({ MapScale.X / 2.0f, -(MapScale.Y - 192.0f) });
}

void TownSecondFloorLeft::Update(float _Delta)
{

}