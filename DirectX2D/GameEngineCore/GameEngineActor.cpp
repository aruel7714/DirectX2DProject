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
	// ���߿� ������ �ɰ�.

	return GetParent<GameEngineLevel>();
}