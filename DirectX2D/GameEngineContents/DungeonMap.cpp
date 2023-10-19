#include "PreCompile.h"
#include "DungeonMap.h"

DungeonMap::DungeonMap()
{
}

DungeonMap::~DungeonMap()
{
}

void DungeonMap::Start()
{

}
void DungeonMap::Update(float _Delta)
{

}

void DungeonMap::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = _PrevLevel;
}
void DungeonMap::LevelEnd(GameEngineLevel* _NextLevel)
{
	NextLevel = _NextLevel;;
}