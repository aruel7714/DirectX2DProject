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
	TopRenderer->SetImageScale({ 1280.0f, 288.0f });

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	TopRenderer->Transform.SetLocalPosition({ 0.0f, HalfWindowScale.Y });
	TopRenderer->GetColorData().MulColor = float4::ZERONULL;

	BottomRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::Fade);
	BottomRenderer->SetImageScale({ 1280.0f, 288.0f });
	BottomRenderer->Transform.SetLocalPosition({ 0.0f, -HalfWindowScale.Y });
	BottomRenderer->GetColorData().MulColor = float4::ZERONULL;

	/*BossText = CreateComponent<GameEngineUIRenderer>(RenderOrder::Fade);
	BossText->SetText("µ¸¿ò", "º§¸®¾Ë", 20.0f, float4::WHITE, FW1_LEFT);
	BossText->GetColorData().MulColor.A = 0.0f;*/

	BossTitle = CreateComponent<GameEngineUIRenderer>(RenderOrder::Fade);
	BossTitle->SetText("µ¸¿ò", "º§¸®¾Ë", 50.0f, float4::WHITE, FW1_LEFT);
	BossTitle->Transform.SetLocalPosition({ -HalfWindowScale.X + 45.0f, -HalfWindowScale.Y + 144.0f + 96.0f });

	BossSubTitle = CreateComponent<GameEngineUIRenderer>(RenderOrder::Fade);
	BossSubTitle->SetText("µ¸¿ò", "°¨¿ÁÀÇ ¼ö¹®Àå", 20.0f, float4::WHITE, FW1_LEFT);
	BossSubTitle->Transform.SetLocalPosition({ -HalfWindowScale.X + 60.0f, -HalfWindowScale.Y + 144.0f + 96.0f + 30.0f });
}
void BossSpawnFadeOut::Update(float _Delta)
{
	TopRenderer->GetColorData().MulColor.A += _Delta / 0.3f;
	BottomRenderer->GetColorData().MulColor.A += _Delta / 0.3f;
	//BossText->GetColorData().MulColor.A += _Delta / 0.3f;

	if (TopRenderer->GetColorData().MulColor.A >= 0.5f && BottomRenderer->GetColorData().MulColor.A >= 0.5f)
	{
		DeathTime += _Delta;
	}

	if (DeathTime >= 3.0f)
	{
		Death();
	}
}