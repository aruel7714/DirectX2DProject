#include "PreCompile.h"
#include "BackCloud.h"

BackCloud::BackCloud()
{
}

BackCloud::~BackCloud()
{
}

void BackCloud::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BackGround);
		Renderer->SetSprite("BackCloud2.png");
		Renderer2 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BackGround);
		Renderer2->SetSprite("BackCloud2.png");

		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BackCloud2.png");

		float4 Scale = Texture->GetScale();

		float4 HScale = Scale.Half();
		HScale.Y *= -1.0f;

		//Transform.SetLocalPosition(HScale);

		//float4 HScale = Texture->GetScale().Half();
		//HScale.X -= 0.0f;
		//HScale.Y *= 0.0f;

		float4 HScale2 = HScale;
		HScale2.X += Scale.X;
		HScale2.X -= 1.0f;

		/*float4 HScale2 = HScale;
		HScale2.X = 640.0f + 1280.0f;*/

		Renderer->Transform.SetLocalPosition(HScale);
		Renderer2->Transform.SetLocalPosition(HScale2);
	}
}
void BackCloud::Update(float _Delta)
{
	float Speed = 50.0f;

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

	//if (-640.0f <= Renderer->Transform.GetWorldPosition().X)
	//{
	//	Renderer->Transform.SetLocalPosition({ 640.0f + 1280.0f, 0.0f });
	//}

	//if (-640.0f <= Renderer2->Transform.GetWorldPosition().X)
	//{
	//	Renderer2->Transform.SetLocalPosition({ 640.0f + 1280.0f, 0.0f });
	//}
}