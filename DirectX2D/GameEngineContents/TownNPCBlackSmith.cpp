#include "PreCompile.h"
#include "TownNPCBlackSmith.h"

TownNPCBlackSmith::TownNPCBlackSmith()
{
}

TownNPCBlackSmith::~TownNPCBlackSmith()
{
}

void TownNPCBlackSmith::Start()
{
	HakenRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	HakenRenderer->CreateAnimation("Haken_Idle", "BlackSmith_Haken");
	HakenRenderer->SetSprite("BlackSmith_Haken");
	//HakenRenderer->SetSamplerState(SamplerOption::POINT);

	float4 Scale = HakenRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	HakenRenderer->SetImageScale(Scale);

	HakenRenderer->SetPivotType(PivotType::Bottom);

	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;

	Transform.SetLocalPosition({ MapScale.X - 992.0f, -(MapScale.Y - 192.0f) });

	HakenRenderer->ChangeAnimation("Haken_Idle");

	{
		HakenCollision = CreateComponent<GameEngineCollision>(CollisionType::NPC);
		HakenCollision->SetCollisionType(ColType::AABBBOX2D);
		HakenCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 2.0f, 1.0f });
		HakenCollision->Transform.SetLocalScale({ Scale.X, Scale.Y, 1.0f });
	}
}

void TownNPCBlackSmith::Update(float _Delta)
{

}