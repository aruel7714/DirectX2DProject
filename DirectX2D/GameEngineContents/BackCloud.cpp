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

		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BackCloud2.png");

		
		
		float4 HScale = Texture->GetScale().Half();
		HScale.X -= 640.0f;
		HScale.Y *= 0.0f;

		Renderer->Transform.SetLocalPosition(HScale);
	}
}
void BackCloud::Update(float _Delta)
{

}