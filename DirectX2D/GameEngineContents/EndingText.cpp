#include "PreCompile.h"
#include "EndingText.h"

EndingText::EndingText()
{
}

EndingText::~EndingText()
{
}

void EndingText::Start()
{
	TextRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Text);
	TextRenderer->SetText("Perfect DOS VGA 437", "감사합니다.", 60.0f, float4::WHITE, FW1_CENTER);
	Transform.SetLocalPosition({ 940.0f, -720.0f });
}
void EndingText::Update(float _Delta)
{
	Transform.AddLocalPosition(float4::UP * _Delta * 50.0f);
}