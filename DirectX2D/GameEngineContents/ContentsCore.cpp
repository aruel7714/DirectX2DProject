#include "PreCompile.h"
#include "ContentsCore.h"

#include "PlayLevel.h"
#include "TitleLevel.h"
#include "TownLevel.h"

#include "Level1F.h"
#include "Level1F_Inn.h"
#include "Level1F_Shop.h"

#include "BeforeBossEncounterLevel.h"
#include "BossEncounterLevel.h"
#include "AfterBossEncounterLevel.h"

void LevelChangeWindow::Start()
{

}
void LevelChangeWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (ImGui::Button("TitleLevel"))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (ImGui::Button("TownLevel"))
	{
		GameEngineCore::ChangeLevel("TownLevel");
	}
	if (ImGui::Button("Level1F"))
	{
		GameEngineCore::ChangeLevel("Level1F");
	}
	if (ImGui::Button("BeforeBossEncounterLevel"))
	{
		GameEngineCore::ChangeLevel("BeforeBossEncounterLevel");
	}
	if (ImGui::Button("BossEncounterLevel"))
	{
		GameEngineCore::ChangeLevel("BossEncounterLevel");
	}
	
}

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	GameEngineGUI::CreateGUIWindow<LevelChangeWindow>("LevelChange");

	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<TownLevel>("TownLevel");
	GameEngineCore::CreateLevel<Level1F>("Level1F");
	GameEngineCore::CreateLevel<Level1F_Inn>("Level1F_Inn");
	GameEngineCore::CreateLevel<Level1F_Shop>("Level1F_Shop");
	
	GameEngineCore::CreateLevel<BeforeBossEncounterLevel>("BeforeBossEncounterLevel");
	GameEngineCore::CreateLevel<BossEncounterLevel>("BossEncounterLevel");
	GameEngineCore::CreateLevel<AfterBossEncounterLevel>("AfterBossEncounterLevel");
	//GameEngineCore::ChangeLevel("TownLevel");
	GameEngineCore::ChangeLevel("TitleLevel");
	//GameEngineCore::ChangeLevel("PlayLevel");

	//// 회전방향을 외적으로 알아내는 방법
	//float4 PlayerPos = {3, 5};
	//float4 MonsterPos = {5, 5};

	//float4 PlayerDir = { 0, 1, 0 };
	//float4 PlayerLook = (PlayerPos - MonsterPos).NormalizeReturn();


	//float4 Check = float4::Cross3D(PlayerDir, PlayerLook);

	//// float4 Rev = float4::Cross3D({0, 10, 0}, { 0.01f, -10.0f, 0 });

	//if (0 > Check.Z)
	//{
	//	// 왼쪽으로 돌아라.
	//}

	//int a = 0;
	GameEngineRenderTarget::IsDepth = false;
}

void ContentsCore::Update(float _Delta)
{
	//HDC DC;
	//{
	//	// 윈도우 클리어
	//	DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();
	//	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	//	Rectangle(DC, 0, 0, WinScale.iX(), WinScale.iY());
	//}


	
	//	GameEngineCore::MainWindow.DoubleBuffering();
	//}
}

void ContentsCore::Release()
{

}