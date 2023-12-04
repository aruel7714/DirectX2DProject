#include "PreCompile.h"
#include "BossSpawnTrigger.h"

BossSpawnTrigger::BossSpawnTrigger()
{
}

BossSpawnTrigger::~BossSpawnTrigger()
{
}

void BossSpawnTrigger::Start()
{
	BossSpawnTriggerCollision = CreateComponent<GameEngineCollision>(CollisionType::Trigger);
	BossSpawnTriggerCollision->SetCollisionType(ColType::AABBBOX2D);
}
void BossSpawnTrigger::Update(float _Delta)
{

}

void BossSpawnTrigger::SetMoveTriggerScale(float4 _Scale)
{
	BossSpawnTriggerCollision->Transform.SetLocalScale(_Scale);
}
void BossSpawnTrigger::SetMoveTriggerPosition(float4 _Position)
{
	BossSpawnTriggerCollision->Transform.SetLocalPosition(_Position);
}