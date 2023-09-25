#include "PreCompile.h"
#include "TownNPCBoutique.h"

TownNPCBoutique::TownNPCBoutique()
{
}

TownNPCBoutique::~TownNPCBoutique()
{
}

void TownNPCBoutique::Start()
{
	BlochRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	BlochRenderer->CreateAnimation("Bloch_Idle", "Boutique_Bloch");
	BlochRenderer->SetSprite("Boutique_Bloch");
	//BlochRenderer->SetSamplerState(SamplerOption::POINT);

	float4 Scale = BlochRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	BlochRenderer->SetImageScale(Scale);

	BlochRenderer->SetPivotType(PivotType::Bottom);

	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;

	Transform.SetLocalPosition({ 883.0f, -(MapScale.Y - 192.0f - 576.0f) });

	BlochRenderer->ChangeAnimation("Bloch_Idle");
	BlochRenderer->Transform.SetLocalScale({ -abs(Transform.GetLocalScale().X), Transform.GetLocalScale().Y });
}

void TownNPCBoutique::Update(float _Delta)
{

}