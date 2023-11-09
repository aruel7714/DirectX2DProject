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
	if (GameEngineInput::IsPress(VK_ESCAPE, this))
	{
		GameEngineCore::ChangeLevel("TownLevel");
	}
}

void OpeningLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}
void OpeningLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}