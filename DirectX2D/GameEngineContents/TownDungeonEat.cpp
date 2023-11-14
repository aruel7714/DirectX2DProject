#include "PreCompile.h"
#include "TownDungeonEat.h"

TownDungeonEat::TownDungeonEat()
{
}

TownDungeonEat::~TownDungeonEat()
{
}

void TownDungeonEat::Start()
{
	EatRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	EatRenderer->CreateAnimation("DungeonEat_Start", "DungeonEat", 0.07f, -1, -1, false);
	EatRenderer->SetSprite("DungeonEat");

	float4 Scale = EatRenderer->GetCurSprite().Texture->GetScale() * 4.0f;

	EatRenderer->SetImageScale(Scale);
	EatRenderer->SetPivotType(PivotType::Bottom);
	EatRenderer->ChangeAnimation("DungeonEat_Start");
}

void TownDungeonEat::Update(float _Delta)
{

}