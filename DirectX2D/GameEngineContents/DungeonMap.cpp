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

	// �̹� ���ο� TitleLevel�� �����Ѵ�.
	if (AllLevel.end() == Finditer)
	{
		MsgBoxAssert(Upper + "�� �̸��� ���� GameEngineLevel�� �������� �ʽ��ϴ�.");
		return nullptr;
	}
	
	return Finditer->second.get();
}