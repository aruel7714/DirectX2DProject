#include "PreCompile.h"
#include "OpeningLevel.h"

OpeningLevel::OpeningLevel()
{
}

OpeningLevel::~OpeningLevel()
{
}

void OpeningLevel::Start()
{
	GameEngineInput::AddInputObject(this);

	
}
void OpeningLevel::Update(float _Delta)
{
}

void OpeningLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}
void OpeningLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}