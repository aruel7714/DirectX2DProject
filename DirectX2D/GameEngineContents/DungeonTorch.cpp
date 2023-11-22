#include "PreCompile.h"
#include "DungeonTorch.h"

DungeonTorch::DungeonTorch()
{
}

DungeonTorch::~DungeonTorch()
{
}

void DungeonTorch::Start()
{
	TorchRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DungeonProp);
	TorchRenderer->CreateAnimation("Torch_Idle", "Torch");
	TorchRenderer->SetSprite("Torch");

	float4 Scale = TorchRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	TorchRenderer->SetImageScale(Scale);

	TorchRenderer->SetPivotType(PivotType::Bottom);
	
	TorchRenderer->ChangeAnimation("Torch_Idle");
}
void DungeonTorch::Update(float _Delta)
{

}