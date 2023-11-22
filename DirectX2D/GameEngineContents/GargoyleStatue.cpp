#include "PreCompile.h"
#include "GargoyleStatue.h"

GargoyleStatue::GargoyleStatue()
{
}

GargoyleStatue::~GargoyleStatue()
{
}

void GargoyleStatue::Start()
{
	GameEngineSprite::CreateSingle("GargoyleBase.png");
	GameEngineSprite::CreateSingle("GargoyleIdle.png");

	StatueBaseRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DungeonProp);
	StatueBaseRenderer->SetSprite("GargoyleBase.png");
	float4 BaseScale = StatueBaseRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	StatueBaseRenderer->SetImageScale(BaseScale);
	StatueBaseRenderer->SetPivotType(PivotType::Bottom);

	GargoyleRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DungeonProp);
	GargoyleRenderer->SetSprite("GargoyleIdle.png");
	float4 GargoyleScale = GargoyleRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	GargoyleRenderer->SetImageScale(GargoyleScale);
	GargoyleRenderer->SetPivotType(PivotType::Bottom);

	GargoyleRenderer->Transform.SetLocalPosition({ 0.0f, StatueBaseRenderer->GetImageTransform().GetLocalScale().Y });
}

void GargoyleStatue::Update(float _Delta)
{

}