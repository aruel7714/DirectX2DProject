#include "PreCompile.h"
#include "TownNPCBuilder.h"

TownNPCBuilder::TownNPCBuilder()
{
}

TownNPCBuilder::~TownNPCBuilder()
{
}

void TownNPCBuilder::Start()
{
	YulfordRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	YulfordRenderer->CreateAnimation("Yulford_Idle", "Builder_Yulford");
	YulfordRenderer->SetSprite("Builder_Yulford");
	YulfordRenderer->SetSamplerState(SamplerOption::POINT);

	float4 Scale = YulfordRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	YulfordRenderer->SetImageScale(Scale);
	YulfordRenderer->SetPivotType(PivotType::Bottom);

	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;

	//Transform.SetLocalPosition({ MapScale.X - 1280.0f, -(MapScale.Y - 192.0f - 576.0f) });

	YulfordRenderer->ChangeAnimation("Millia_Idle");
	YulfordRenderer->Transform.SetLocalScale({ -abs(Transform.GetLocalScale().X), Transform.GetLocalScale().Y });
}