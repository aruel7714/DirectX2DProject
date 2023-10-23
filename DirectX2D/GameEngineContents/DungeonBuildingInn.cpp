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
	GameEngineSprite::CreateSingle("DungeonInn.png");
	DungeonInnRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrderDungeon::Building);
	DungeonInnRenderer->SetSprite("DungeonInn.png");

	ImageScale = GameEngineTexture::Find("DungeonInn.png")->GetScale() * 4.0f;

	DungeonInnRenderer->SetImageScale(ImageScale);
	DungeonInnRenderer->SetPivotType(PivotType::Bottom);
}
void DungeonBuildingInn::Update(float _Delta)
{

}

void DungeonBuildingInn::SetBuildingPosition(float4 _Pos)
{
	Transform.SetLocalPosition(_Pos);
}