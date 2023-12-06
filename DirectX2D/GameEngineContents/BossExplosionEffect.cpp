#include "PreCompile.h"
#include "BossExplosionEffect.h"

BossExplosionEffect::BossExplosionEffect()
{
}

BossExplosionEffect::~BossExplosionEffect()
{
}

void BossExplosionEffect::Start()
{
	ExplosionRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::FrontProp);
	ExplosionRenderer->CreateAnimation("Explosion", "Die", 0.05f, -1, -1, false);
	ExplosionRenderer->SetSprite("Die");
	float4 Scale = ExplosionRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	ExplosionRenderer->SetImageScale(Scale);

	ExplosionRenderer->ChangeAnimation("Explosion");
}
void BossExplosionEffect::Update(float _Delta)
{
	if (true == ExplosionRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}