#include "PreCompile.h"
#include "TownDungeonTrigger.h"
#include "TownDungeonIngurgitate.h"

TownDungeonTrigger::TownDungeonTrigger()
{
}

TownDungeonTrigger::~TownDungeonTrigger()
{
}

void TownDungeonTrigger::Start()
{
	DungeonTriggerCollision = CreateComponent<GameEngineCollision>(CollisionType::Trigger);
	DungeonTriggerCollision->SetCollisionType(ColType::AABBBOX2D);

	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;

	DungeonTriggerCollision->Transform.SetLocalPosition({ 3775.0f, -(MapScale.Y - 192.0f + 32.0f - 1.0f)});
	DungeonTriggerCollision->Transform.SetLocalScale({ 1150.0f, 64.0f, 1.0f });
}

void TownDungeonTrigger::Update(float _Delta)
{
	
}