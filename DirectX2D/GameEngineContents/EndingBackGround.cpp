#include "PreCompile.h"
#include "EndingBackGround.h"

EndingBackGround::EndingBackGround()
{
}

EndingBackGround::~EndingBackGround()
{
}

void EndingBackGround::Start()
{
	BackGroundRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BackGround2);
	BackGroundRenderer->SetSampler("EngineBaseWRAPSampler");
	BackGroundRenderer->SetSprite("TownBG_Day.png");

	float4 Scale = BackGroundRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BackGroundRenderer->SetImageScale(Scale);
	Transform.SetLocalPosition({ Scale.X / 2.0f, -400.0f });

	SetSpeed(20.0f);
}
void EndingBackGround::Update(float _Delta)
{
	BackGroundRenderer->RenderBaseInfoValue.VertexUVPlus += Speed * _Delta;
}

void EndingBackGround::SetSpeed(float _Speed)
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	Speed = -_Speed / WindowScale.X;
}