#include "PreCompile.h"
#include "DungeonNPCInn.h"

DungeonNPCInn::DungeonNPCInn()
{
}

DungeonNPCInn::~DungeonNPCInn()
{
}

void DungeonNPCInn::Start()
{
	InnRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	InnRenderer->CreateAnimation("Inn_Idle", "Inn");
	InnRenderer->SetSprite("Inn");

	float4 Scale = InnRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	InnRenderer->SetImageScale(Scale);
	InnRenderer->SetPivotType(PivotType::Bottom);

	InnRenderer->ChangeAnimation("Inn_Idle");

	InnRenderer->LeftFlip();

	{
		InnCollision = CreateComponent<GameEngineCollision>(CollisionType::NPC);
		InnCollision->SetCollisionType(ColType::AABBBOX2D);
		InnCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 2.0f, 1.0f });
		InnCollision->Transform.SetLocalScale({ Scale.X, Scale.Y, 1.0f });
	}
}
void DungeonNPCInn::Update(float _Delta)
{

}

void DungeonNPCInn::SetInnPosition(float4 _Pos)
{
	Transform.SetLocalPosition(_Pos);
}