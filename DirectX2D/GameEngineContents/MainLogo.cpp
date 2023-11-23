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
		Renderer = CreateComponent<GameEngineSpriteRenderer>(TitleRenderOrder::UI);
		Renderer->SetSprite("MainLogo4x.png");

		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("MainLogo4x.png");

		Renderer->SetPivotType(PivotType::Bottom);

		float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
		Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y - 45.0f, -500.0f });

	}
}
void MainLogo::Update(float _Delta)
{

}