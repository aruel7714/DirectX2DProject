#include "PreCompile.h"
#include "BoseExplosionEffect.h"

BoseExplosionEffect::BoseExplosionEffect()
{
}

BoseExplosionEffect::~BoseExplosionEffect()
{
}

void BoseExplosionEffect::Start()
{
	ExplosionRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::FrontProp);
	ExplosionRenderer->CreateAnimation("Explosion", "Die", 0.025f, -1, -1, false);
	ExplosionRenderer->SetSprite("Die");
	float4 Scale = ExplosionRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	ExplosionRenderer->SetImageScale(Scale);

	ExplosionRenderer->ChangeAnimation("Explosion");
}
void BoseExplosionEffect::Update(float _Delta)
{
	if (true == ExplosionRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}