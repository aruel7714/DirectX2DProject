#include "PreCompile.h"
#include "BossSpawnFadeOut.h"

BossSpawnFadeOut::BossSpawnFadeOut()
{
}

BossSpawnFadeOut::~BossSpawnFadeOut()
{
}

void BossSpawnFadeOut::Start()
{
	TopRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::Fade);

	float4 Scale = TopRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	TopRenderer->SetImageScale(Scale);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	TopRenderer->Transform.SetLocalPosition({ 0.0f, HalfWindowScale.Y });
	TopRenderer->GetColorData().MulColor.A = 0.0f;

	BottomRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::Fade);
	BottomRenderer->SetImageScale(Scale);
	BottomRenderer->Transform.SetLocalPosition({ 0.0f, -HalfWindowScale.Y });
	BottomRenderer->GetColorData().MulColor.A = 0.0f;
}
void BossSpawnFadeOut::Update(float _Delta)
{
	TopRenderer->GetColorData().MulColor.A += _Delta / 0.3f;
	BottomRenderer->GetColorData().MulColor.A += _Delta / 0.3f;
}