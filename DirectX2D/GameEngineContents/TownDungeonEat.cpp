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
	EatRenderer->CreateAnimation("DungeonEat_Spawn", "DungeonEat", 0.07f, 0, 8, false);
	EatRenderer->CreateAnimation("DungeonEat_Down", "DungeonEat", 0.07f, 9, 27, false);
	EatRenderer->SetSprite("DungeonEat");

	float4 Scale = EatRenderer->GetCurSprite().Texture->GetScale() * 4.0f;

	EatRenderer->SetImageScale(Scale);
	EatRenderer->SetPivotType(PivotType::Bottom);
	EatRenderer->ChangeAnimation("DungeonEat_Spawn");
}

void TownDungeonEat::Update(float _Delta)
{
	if (EatRenderer->IsCurAnimation("DungeonEat_Spawn"))
	{
		if (EatRenderer->IsCurAnimationEnd())
		{
			EatRenderer->ChangeAnimation("DungeonEat_Down");
		}
	}
}