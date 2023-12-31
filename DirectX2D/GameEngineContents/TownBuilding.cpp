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

		//TrainingSchool->SetSamplerState(SamplerOption::POINT);
		TrainingSchool->SetImageScale(ImageScale);
		TrainingSchool->SetPivotType(PivotType::Bottom);

		TrainingSchool->Transform.SetLocalPosition({ 640.0f, -(MapScale.Y - 192.0f) });
	}

	{
		Shop = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Building);
		Shop->SetSprite("Shop.png");

		ImageScale = GameEngineTexture::Find("Shop.png")->GetScale() * 4.0f;

		//Shop->SetSamplerState(SamplerOption::POINT);
		Shop->SetImageScale(ImageScale);
		Shop->SetPivotType(PivotType::Bottom);

		// SecondFloor.Y = 144 * 4 = 576
		Shop->Transform.SetLocalPosition({ MapScale.X - 1280.0f, -(MapScale.Y - 192.0f - 576.0f) });
	}

	{
		BlackSmith = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Building);
		BlackSmith->SetSprite("BlackSmith.png");

		ImageScale = GameEngineTexture::Find("BlackSmith.png")->GetScale() * 4.0f;

		//BlackSmith->SetSamplerState(SamplerOption::POINT);
		BlackSmith->SetImageScale(ImageScale);
		BlackSmith->SetPivotType(PivotType::Bottom);

		BlackSmith->Transform.SetLocalPosition({ MapScale.X - 992.0f, -(MapScale.Y - 192.0f) });
	}

	{
		Boutique = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Building);
		Boutique->SetSprite("Boutique.png");

		ImageScale = GameEngineTexture::Find("Boutique.png")->GetScale() * 4.0f;

		//Boutique->SetSamplerState(SamplerOption::POINT);
		Boutique->SetImageScale(ImageScale);
		Boutique->SetPivotType(PivotType::Bottom);

		Boutique->Transform.SetLocalPosition({ 883.0f, -(MapScale.Y - 192.0f - 576.0f) });
	}

	{
		Gunsmith = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Building);
		Gunsmith->SetSprite("Gunsmith.png");

		ImageScale = GameEngineTexture::Find("Gunsmith.png")->GetScale() * 4.0f;

		//Gunsmith->SetSamplerState(SamplerOption::POINT);
		Gunsmith->SetImageScale(ImageScale);
		Gunsmith->SetPivotType(PivotType::Bottom);

		Gunsmith->Transform.SetLocalPosition({ MapScale.X - 524.0f, -(MapScale.Y - 192.0f - 576.0f) });
	}

	{
		Temple = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Building);
		Temple->SetSprite("Temple.png");

		ImageScale = GameEngineTexture::Find("Temple.png")->GetScale() * 4.0f;

		//Temple->SetSamplerState(SamplerOption::POINT);
		Temple->SetImageScale(ImageScale);
		Temple->SetPivotType(PivotType::Bottom);

		Temple->Transform.SetLocalPosition({ MapScale.Half().X + 88.0f, -(MapScale.Y - 192.0f - 448.0f)});
	}

	{
		FrontTemple = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::FrontBuilding);
		FrontTemple->SetSprite("TempleFront.png");

		ImageScale = GameEngineTexture::Find("TempleFront.png")->GetScale() * 4.0f;

		//FrontTemple->SetSamplerState(SamplerOption::POINT);
		FrontTemple->SetImageScale(ImageScale);
		FrontTemple->SetPivotType(PivotType::Bottom);

		FrontTemple->Transform.SetLocalPosition({ MapScale.Half().X - 136.0f, -(MapScale.Y - 192.0f - 448.0f) });
	}

	{
		BuildingOffice = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BackBuilding);
		BuildingOffice->SetSprite("BuildingOffice.png");

		ImageScale = GameEngineTexture::Find("BuildingOffice.png")->GetScale() * 4.0f;

		BuildingOffice->SetImageScale(ImageScale);
		BuildingOffice->SetPivotType(PivotType::Bottom);

		BuildingOffice->Transform.SetLocalPosition({ 2436.0f, -(MapScale.Y - 192.0f) });
	}

	{
		BlackSmithDisplay = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BuildingProp);
		BlackSmithDisplay->SetSprite("BlackSmithDisplay.png");

		ImageScale = GameEngineTexture::Find("BlackSmithDisplay.png")->GetScale() * 4.0f;

		BlackSmithDisplay->SetImageScale(ImageScale);
		BlackSmithDisplay->SetPivotType(PivotType::Bottom);

		BlackSmithDisplay->Transform.SetLocalPosition({ MapScale.X - 992.0f, -(MapScale.Y - 192.0f) });
	}

	{
		TrainingTarget = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BuildingProp);
		TrainingTarget->SetSprite("Target.png");

		ImageScale = GameEngineTexture::Find("Target.png")->GetScale() * 4.0f;

		TrainingTarget->SetImageScale(ImageScale);
		TrainingTarget->SetPivotType(PivotType::Bottom);

		TrainingTarget->Transform.SetLocalPosition({ 1204.0f, -(MapScale.Y - 192.0f) });
	}

	

}

void TownBuilding::Update(float _Delta)
{
	float4 Pos = TrainingSchool->Transform.GetWorldPosition();
	int a = 0;
}