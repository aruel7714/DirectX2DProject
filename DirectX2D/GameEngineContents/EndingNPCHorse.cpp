#include "PreCompile.h"
#include "EndingNPCHorse.h"

EndingNPCHorse::EndingNPCHorse()
{
}

EndingNPCHorse::~EndingNPCHorse()
{
}

void EndingNPCHorse::Start()
{
	HorseRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::FrontProp);
	HorseRenderer->CreateAnimation("Horse_Move", "Horse");
	HorseRenderer->SetSprite("Horse");
	float4 Scale = HorseRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	HorseRenderer->SetImageScale(Scale);
	HorseRenderer->SetPivotType(PivotType::Bottom);

	HorseRenderer->ChangeAnimation("Horse_Move");
}
void EndingNPCHorse::Update(float _Delta)
{

}