#include "PreCompile.h"
#include "TownSky.h"

TownSky::TownSky()
{
}

TownSky::~TownSky()
{
}

void TownSky::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->SetSprite("Sky_Day2.png");

		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Sky_Day2.png");

		float4 HScale = Texture->GetScale().Half();
		HScale.Y *= -1.0f;

		Renderer->Transform.SetLocalPosition(HScale);
	}
}
void TownSky::Update(float _Delta)
{

}