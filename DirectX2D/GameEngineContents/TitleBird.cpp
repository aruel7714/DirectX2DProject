#include "PreCompile.h"
#include "TitleBird.h"

TitleBird::TitleBird()
{
}

TitleBird::~TitleBird()
{
}

void TitleBird::Start()
{
	TitleBirdRenderer = CreateComponent<GameEngineSpriteRenderer>(TitleRenderOrder::TitleBird);

	TitleBirdRenderer->CreateAnimation("TitleBird_Move", "Bird", 0.07f);
	TitleBirdRenderer->SetSprite("Bird");
	//TitleBirdRenderer->SetSamplerState(SamplerOption::POINT);

	float4 Scale = TitleBirdRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	TitleBirdRenderer->SetImageScale(Scale);

	Transform.SetLocalPosition({ 0.0f, -(GameEngineCore::MainWindow.GetScale().Half().Half().Y * 3) });

	TitleBirdRenderer->ChangeAnimation("TitleBird_Move");
}

void TitleBird::Update(float _Delta)
{
	float Speed = 90.0f;

	Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
}