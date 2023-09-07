#include "PreCompile.h"
#include "MainLogo.h"

MainLogo::MainLogo()
{
}

MainLogo::~MainLogo()
{
}

void MainLogo::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->SetSprite("MainLogo2.png");

		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("MainLogo2.png");

		float4 HScale = Texture->GetScale().Half();
		HScale.X *= 0.0f;
		HScale.Y *= 1.0f;

		Renderer->Transform.SetLocalPosition(HScale);
	}
}
void MainLogo::Update(float _Delta)
{

}