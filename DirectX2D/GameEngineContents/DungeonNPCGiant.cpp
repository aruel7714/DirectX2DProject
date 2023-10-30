#include "PreCompile.h"
#include "DungeonNPCGiant.h"

DungeonNPCGiant::DungeonNPCGiant()
{
}

DungeonNPCGiant::~DungeonNPCGiant()
{
}

void DungeonNPCGiant::Start()
{
	GiantRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	GiantRenderer->CreateAnimation("Giant_Idle", "Giant");
	GiantRenderer->SetSprite("Giant");

	float4 Scale = GiantRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	GiantRenderer->SetImageScale(Scale);
	GiantRenderer->SetPivotType(PivotType::Bottom);

	GiantRenderer->ChangeAnimation("Giant_Idle");

	GiantRenderer->LeftFlip();

	{
		GiantCollision = CreateComponent<GameEngineCollision>(CollisionType::NPC);
		GiantCollision->SetCollisionType(ColType::AABBBOX2D);
		GiantCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 2.0f, 1.0f });
		GiantCollision->Transform.SetLocalScale({ Scale.X, Scale.Y, 1.0f });
	}
}
void DungeonNPCGiant::Update(float _Delta)
{

}

void DungeonNPCGiant::SetGiantPosition(float4 _Pos)
{
	Transform.SetLocalPosition(_Pos);
}