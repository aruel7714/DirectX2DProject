#include "PreCompile.h"
#include "TownNPCPistolMan.h"

TownNPCPistolMan::TownNPCPistolMan()
{
}

TownNPCPistolMan::~TownNPCPistolMan()
{
}

void TownNPCPistolMan::Start()
{
	FiatRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	FiatRenderer->CreateAnimation("Fiat_Idle", "PistolMan_Fiat");
	FiatRenderer->SetSprite("PistolMan_Fiat");
	FiatRenderer->SetSamplerState(SamplerOption::POINT);

	float4 Scale = FiatRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	FiatRenderer->SetImageScale(Scale);
	FiatRenderer->SetPivotType(PivotType::Bottom);

	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;

	Transform.SetLocalPosition({ MapScale.X - 524.0f, -(MapScale.Y - 192.0f - 576.0f) });

	FiatRenderer->ChangeAnimation("Fiat_Idle");
	FiatRenderer->Transform.SetLocalScale({ -abs(Transform.GetLocalScale().X), Transform.GetLocalScale().Y });
}

void TownNPCPistolMan::Update(float _Delta)
{

}