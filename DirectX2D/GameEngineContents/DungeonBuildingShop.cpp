#include "PreCompile.h"
#include "DungeonBuildingShop.h"

DungeonBuildingShop::DungeonBuildingShop()
{
}

DungeonBuildingShop::~DungeonBuildingShop()
{
}

void DungeonBuildingShop::Start()
{
	GameEngineSprite::CreateSingle("InDungeonShop.png");
	DungeonShopRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DungeonBuilding);
	DungeonShopRenderer->SetSprite("InDungeonShop.png");

	ImageScale = GameEngineTexture::Find("InDungeonShop.png")->GetScale() * 4.0f;

	DungeonShopRenderer->SetImageScale(ImageScale);
	DungeonShopRenderer->SetPivotType(PivotType::Bottom);
}
void DungeonBuildingShop::Update(float _Delta)
{

}

void DungeonBuildingShop::SetBuildingPosition(float4 _Pos)
{
	Transform.SetLocalPosition(_Pos);
}