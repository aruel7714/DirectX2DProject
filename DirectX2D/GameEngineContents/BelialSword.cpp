#include "PreCompile.h"
#include "BelialSword.h"

BelialSword::BelialSword()
{
}

BelialSword::~BelialSword()
{
}

void BelialSword::Start()
{
	SwordRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);
	
}
void BelialSword::Update(float _Delta)
{

}