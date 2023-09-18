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
		Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BackGround);
		Renderer->SetSprite("FrontCloud2.png");

		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("FrontCloud2.png");



		float4 HScale = Texture->GetScale().Half();
		//HScale.X -= 640.0f;
		//HScale.Y *= 0.0f;
		HScale.Y *= -1.0f;

		Transform.SetLocalPosition(HScale);
	}
}
void FrontCloud::Update(float _Delta)
{

}