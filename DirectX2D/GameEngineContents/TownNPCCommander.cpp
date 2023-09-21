#include "PreCompile.h"
#include "TownNPCCommander.h"

TownNPCCommander::TownNPCCommander()
{
}

TownNPCCommander::~TownNPCCommander()
{
}

void TownNPCCommander::Start()
{
	CoblovinaRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	CoblovinaRenderer->CreateAnimation("Coblovina_Idle", "Commander_Coblovina");
	CoblovinaRenderer->SetSprite("Commander_Coblovina");
	CoblovinaRenderer->SetSamplerState(SamplerOption::POINT);

	float4 Scale = CoblovinaRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	CoblovinaRenderer->SetImageScale(Scale);
	CoblovinaRenderer->SetPivotType(PivotType::Bottom);
	
	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;

	Transform.SetLocalPosition({ 640.0f, -(MapScale.Y - 192.0f) });

	CoblovinaRenderer->ChangeAnimation("Coblovina_Idle");
}

void TownNPCCommander::Update(float _Delta)
{

}