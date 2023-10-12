#include "PreCompile.h"
#include "TownNPCMerchant.h"

TownNPCMerchant::TownNPCMerchant()
{
}

TownNPCMerchant::~TownNPCMerchant()
{
}

void TownNPCMerchant::Start()
{
	MilliaRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	MilliaRenderer->CreateAnimation("Millia_Idle", "Merchant_Millia");
	MilliaRenderer->SetSprite("Merchant_Millia");
	//MilliaRenderer->SetSamplerState(SamplerOption::POINT);

	float4 Scale = MilliaRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	MilliaRenderer->SetImageScale(Scale);
	MilliaRenderer->SetPivotType(PivotType::Bottom);

	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;

	Transform.SetLocalPosition({ MapScale.X - 1280.0f, -(MapScale.Y - 192.0f - 576.0f) });

	MilliaRenderer->ChangeAnimation("Millia_Idle");
	MilliaRenderer->Transform.SetLocalScale({ -abs(Transform.GetLocalScale().X), Transform.GetLocalScale().Y });

	{
		MilliaCollision = CreateComponent<GameEngineCollision>(CollisionType::NPC);
		MilliaCollision->SetCollisionType(ColType::AABBBOX2D);
		MilliaCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 2.0f, 1.0f });
		MilliaCollision->Transform.SetLocalScale({ Scale.X, Scale.Y, 1.0f });
	}
}

void TownNPCMerchant::Update(float _Delta)
{

}