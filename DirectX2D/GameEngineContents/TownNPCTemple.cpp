#include "PreCompile.h"
#include "TownNPCTemple.h"

TownNPCTemple::TownNPCTemple()
{
}

TownNPCTemple::~TownNPCTemple()
{
}

void TownNPCTemple::Start()
{
	RozenRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	RozenRenderer->CreateAnimation("Rozen_Idle", "Temple_Rozen");
	RozenRenderer->SetSprite("Temple_Rozen");
	//RozenRenderer->SetSamplerState(SamplerOption::POINT);

	float4 Scale = RozenRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	RozenRenderer->SetImageScale(Scale);
	RozenRenderer->SetPivotType(PivotType::Bottom);

	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;

	Transform.SetLocalPosition({ MapScale.Half().X + 88.0f, -(MapScale.Y - 192.0f - 448.0f) });

	RozenRenderer->ChangeAnimation("Rozen_Idle");
	RozenRenderer->Transform.SetLocalScale({ -abs(Transform.GetLocalScale().X), Transform.GetLocalScale().Y });

	{
		RozenCollision = CreateComponent<GameEngineCollision>(CollisionType::NPC);
		RozenCollision->SetCollisionType(ColType::AABBBOX2D);
		RozenCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 2.0f, 1.0f });
		RozenCollision->Transform.SetLocalScale({ Scale.X, Scale.Y, 1.0f });
	}
}

void TownNPCTemple::Update(float _Delta)
{

}