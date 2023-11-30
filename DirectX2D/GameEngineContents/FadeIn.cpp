#include "PreCompile.h"
#include "FadeIn.h"

FadeIn::FadeIn()
{
}

FadeIn::~FadeIn()
{
}

void FadeIn::Start()
{
	BlackRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Fade);
	BlackRenderer->GetColorData().MulColor = float4::ZERONULL;
	BlackRenderer->SetImageScale({ 1280.0f, 720.0f });
}
void FadeIn::Update(float _Delta)
{
	Transform.SetLocalPosition(GetLevel()->GetMainCamera()->Transform.GetWorldPosition());
	BlackRenderer->GetColorData().MulColor.A += _Delta / 1.0f;
}