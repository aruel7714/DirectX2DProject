#include "PreCompile.h"
#include "TownNPCTemple.h"

TownNPCTemple::TownNPCTemple()
{
}

TownNPCTemple::~TownNPCTemple()
{
}

void TownNPCTemple::Start()
{
	RozenRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	RozenRenderer->CreateAnimation("Rozen_Idle", "Temple_Rozen");
	RozenRenderer->SetSprite("Temple_Rozen");
	RozenRenderer->SetSamplerState(SamplerOption::POINT);

	float4 Scale = RozenRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	RozenRenderer->SetImageScale(Scale);
	RozenRenderer->SetPivotType(PivotType::Bottom);

	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;

	Transform.SetLocalPosition({ MapScale.Half().X + 88.0f, -(MapScale.Y - 192.0f - 448.0f) });

	RozenRenderer->ChangeAnimation("Rozen_Idle");
	RozenRenderer->Transform.SetLocalScale({ -abs(Transform.GetLocalScale().X), Transform.GetLocalScale().Y });
}

void TownNPCTemple::Update(float _Delta)
{

}