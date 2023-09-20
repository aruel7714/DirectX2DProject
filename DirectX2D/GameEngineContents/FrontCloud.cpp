#include "PreCompile.h"
#include "FrontCloud.h"

FrontCloud::FrontCloud()
{
}

FrontCloud::~FrontCloud()
{
}

void FrontCloud::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(TitleRenderOrder::FrontCloud);
		Renderer->SetSprite("FrontCloud2.png");
		Renderer2 = CreateComponent<GameEngineSpriteRenderer>(TitleRenderOrder::FrontCloud);
		Renderer2->SetSprite("FrontCloud2.png");

		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("FrontCloud2.png");

		float4 Scale = Texture->GetScale();

		float4 HScale = Texture->GetScale().Half();
		HScale.Y *= -1.0f;

		float4 HScale2 = HScale;
		HScale2.X += Scale.X;
		HScale2.X -= 1.0f;

		Renderer->Transform.SetLocalPosition(HScale);
		Renderer2->Transform.SetLocalPosition(HScale2);
	}
}
void FrontCloud::Update(float _Delta)
{
	float Speed = 75.0f;

	Renderer->Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	Renderer2->Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);

	float4 Scale = Renderer->GetCurSprite().Texture->GetScale();

	if (-Scale.Half().X >= Renderer->Transform.GetWorldPosition().X)
	{
		Renderer->Transform.SetLocalPosition({ Scale.Half().X + Scale.X - 2.0f, -Scale.Half().Y });
	}

	if (-Scale.Half().X >= Renderer2->Transform.GetWorldPosition().X)
	{
		Renderer2->Transform.SetLocalPosition({ Scale.Half().X + Scale.X - 2.0f, -Scale.Half().Y });
	}
}