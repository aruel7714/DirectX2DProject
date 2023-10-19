#include "PreCompile.h"
#include "BossEncounterLevel.h"
#include "BossEncounterFloor.h"
#include "BeforeBossEncounterLevel.h"
#include "Player.h"

BossEncounterLevel::BossEncounterLevel()
{
}

BossEncounterLevel::~BossEncounterLevel()
{
}

void BossEncounterLevel::Start()
{
	
	GameEngineSprite::CreateSingle("BossRoom.png");
	GameEngineSprite::CreateSingle("BossRoom_Debug.png");

	BossEncounterFloor = CreateActor<class BossEncounterFloor>(RenderOrderDungeon::Floor);

	MainPlayer = CreateActor<Player>(RenderOrderDungeon::Player);
	MainPlayer->Transform.SetLocalPosition({ 360.0f , -1088.0f });
}
void BossEncounterLevel::Update(float _Delta)
{

}

void BossEncounterLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::string PrevLevelName = _PrevLevel->GetName();

	//_PrevLevel->

	BossEncounterFloor->SetDebugBackGround();
	//MainPlayer->Transform.SetLocalPosition({ 180.0f , -1088.0f });

	if (NextLevel = _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 180.0f , -1088.0f });
	}
}
void BossEncounterLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}