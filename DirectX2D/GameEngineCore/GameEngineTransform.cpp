#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
{
}

GameEngineTransform::~GameEngineTransform()
{
}

void GameEngineTransform::TransformUpdate()
{
	TransData.LocalCalculation();
	TransData.WorldMatrix = TransData.LocalWorldMatrix;

	if (nullptr != Parent)
	{
		TransData.ParentMatrix = Parent->TransData.WorldMatrix;
		TransData.WorldMatrix = TransData.LocalWorldMatrix * TransData.ParentMatrix;
	}
}