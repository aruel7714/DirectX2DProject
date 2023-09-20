#include "PreCompile.h"
#include "TownBuilding.h"

TownBuilding::TownBuilding()
{
}

TownBuilding::~TownBuilding()
{
}

void TownBuilding::Start()
{
	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;

	{
		TrainingSchool = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Building);
		TrainingSchool->SetSprite("TrainingSchool.png");

		ImageScale = GameEngineTexture::Find("TrainingSchool.png")->GetScale() * 4.0f;

		TrainingSchool->SetSamplerState(SamplerOption::POINT);
		TrainingSchool->SetImageScale(ImageScale);
		TrainingSchool->SetPivotType(PivotType::Bottom);

		TrainingSchool->Transform.SetLocalPosition({ 640.0f, -(MapScale.Y - 192.0f) });
	}

	{
		Shop = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Building);
		Shop->SetSprite("Shop.png");

		ImageScale = GameEngineTexture::Find("Shop.png")->GetScale() * 4.0f;

		Shop->SetSamplerState(SamplerOption::POINT);
		Shop->SetImageScale(ImageScale);
		Shop->SetPivotType(PivotType::Bottom);

		// SecondFloor.Y = 144 * 4 = 576
		Shop->Transform.SetLocalPosition({ MapScale.X - 1280.0f, -(MapScale.Y - 192.0f - 576.0f) });
	}

	{
		BlackSmith = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Building);
		BlackSmith->SetSprite("BlackSmith.png");

		ImageScale = GameEngineTexture::Find("BlackSmith.png")->GetScale() * 4.0f;

		BlackSmith->SetSamplerState(SamplerOption::POINT);
		BlackSmith->SetImageScale(ImageScale);
		BlackSmith->SetPivotType(PivotType::Bottom);

		BlackSmith->Transform.SetLocalPosition({ MapScale.X - 992.0f, -(MapScale.Y - 192.0f) });
	}

	

	

}

void TownBuilding::Update(float _Delta)
{
	float4 Pos = TrainingSchool->Transform.GetWorldPosition();
	int a = 0;
}