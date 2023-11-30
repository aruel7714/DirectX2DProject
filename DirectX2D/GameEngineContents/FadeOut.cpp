#include "PreCompile.h"
#include "FadeOut.h"

FadeOut::FadeOut()
{
}

FadeOut::~FadeOut()
{
}

void FadeOut::Start()
{
	BlackRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Fade);
	BlackRenderer->GetColorData().MulColor = float4::ZERO;
	BlackRenderer->SetImageScale({ 1280.0f, 720.0f });
}
void FadeOut::Update(float _Delta)
{
	Transform.SetLocalPosition(GetLevel()->GetMainCamera()->Transform.GetWorldPosition());
	BlackRenderer->GetColorData().MulColor.A -= _Delta / 1.0f;
	if (BlackRenderer->GetColorData().MulColor.A <= 0.0f)
	{
		Death();
	}
}