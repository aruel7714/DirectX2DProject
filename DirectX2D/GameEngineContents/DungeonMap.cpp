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
}
void DungeonMap::LevelEnd(GameEngineLevel* _NextLevel)
{
}

GameEngineLevel* DungeonMap::FindLevel(const std::string& _Name)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Name);
	std::map<std::string, std::shared_ptr<GameEngineLevel>> AllLevel;

	AllLevel = GameEngineCore::GetAllLevel();

	std::map<std::string, std::shared_ptr<GameEngineLevel>>::iterator Finditer = AllLevel.find(Upper);

	// 이미 내부에 TitleLevel이 존재한다.
	if (AllLevel.end() == Finditer)
	{
		MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 존재하지 않습니다.");
		return nullptr;
	}
	
	return Finditer->second.get();
}