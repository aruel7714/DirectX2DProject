#include "PreCompile.h"
#include "LevelFadeOut.h"

LevelFadeOut::LevelFadeOut()
{
}

LevelFadeOut::~LevelFadeOut()
{
}

void LevelFadeOut::Start()
{
	BlackRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Fade);
	BlackRenderer->GetColorData().MulColor = float4::ZERO;
	BlackRenderer->SetImageScale({ 1280.0f, 720.0f });
}
void LevelFadeOut::Update(float _Delta)
{
	Transform.SetLocalPosition(GetLevel()->GetMainCamera()->Transform.GetWorldPosition());
	BlackRenderer->GetColorData().MulColor.A -= _Delta / 1.0f;
	if (BlackRenderer->GetColorData().MulColor.A <= 0.0f)
	{
		Death();
	}
}