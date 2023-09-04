#include "PreCompile.h"
#include "GameEngineActor.h"

GameEngineActor::GameEngineActor() 
{
}

GameEngineActor::~GameEngineActor() 
{
}

GameEngineLevel* GameEngineActor::GetLevel()
{
	// 나중에 문제가 될것.

	return GetParent<GameEngineLevel>();
}