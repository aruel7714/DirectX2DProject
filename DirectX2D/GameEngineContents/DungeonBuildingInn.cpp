#include "PreCompile.h"
#include "DungeonBuildingInn.h"

DungeonBuildingInn::DungeonBuildingInn()
{
}

DungeonBuildingInn::~DungeonBuildingInn()
{
}

void DungeonBuildingInn::Start()
{
	DungeonInnRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrderDungeon::Building);
	DungeonInnRenderer->SetSprite("Inn.png");

	ImageScale = GameEngineTexture::Find("Inn.png")->GetScale() * 4.0f;

	DungeonInnRenderer->SetImageScale(ImageScale);
	DungeonInnRenderer->SetPivotType(PivotType::Bottom);
}
void DungeonBuildingInn::Update(float _Delta)
{

}