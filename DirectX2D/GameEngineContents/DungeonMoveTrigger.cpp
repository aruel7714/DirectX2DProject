#include "PreCompile.h"
#include "DungeonMoveTrigger.h"

DungeonMoveTrigger::DungeonMoveTrigger()
{
}

DungeonMoveTrigger::~DungeonMoveTrigger()
{
}

void DungeonMoveTrigger::Start()
{
	MoveTriggerCollision = CreateComponent<GameEngineCollision>(CollisionType::DungeonTrigger);
	MoveTriggerCollision->SetCollisionType(ColType::AABBBOX2D);
}
void DungeonMoveTrigger::Update(float _Delta)
{

}

void DungeonMoveTrigger::SetMoveTriggerScale(float4 _Scale)
{
	MoveTriggerCollision->Transform.SetLocalScale(_Scale);
}
void DungeonMoveTrigger::SetMoveTriggerPosition(float4 _Position)
{
	MoveTriggerCollision->Transform.SetLocalPosition(_Position);
}


