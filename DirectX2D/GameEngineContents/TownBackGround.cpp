#include "PreCompile.h"
#include "TownBackGround.h"

TownBackGround::TownBackGround()
{
}

TownBackGround::~TownBackGround()
{
}

void TownBackGround::Start()
{
	BackGroundRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BackGround2);
	BackGroundRenderer->SetSprite("TownBG_Day.png");

	float4 Scale = BackGroundRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BackGroundRenderer->SetSampler("EngineBaseWRAPSampler");
	BackGroundRenderer->SetImageScale(Scale);
}
void TownBackGround::Update(float _Delta)
{

}