#include "PreCompile.h"
#include "TownDungeonIngurgitate.h"
#include "Player.h"

TownDungeonIngurgitate::TownDungeonIngurgitate()
{
}

TownDungeonIngurgitate::~TownDungeonIngurgitate()
{
}

void TownDungeonIngurgitate::Start()
{
	IngurgitateRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	IngurgitateRenderer->CreateAnimation("DungeonIngurgitate_Start", "DungeonIngurgitate", 0.07f, -1, -1, false);
	IngurgitateRenderer->SetSprite("DungeonIngurgitate");

	float4 Scale = IngurgitateRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	IngurgitateRenderer->SetImageScale(Scale);

	IngurgitateRenderer->SetPivotType(PivotType::Bottom);
	
	IngurgitateRenderer->ChangeAnimation("DungeonIngurgitate_Start");
}

void TownDungeonIngurgitate::Update(float _Delta)
{

}