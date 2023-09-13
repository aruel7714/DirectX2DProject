#include "PreCompile.h"
#include "ContentsCore.h"
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "TownLevel.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	//GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TownLevel>("TownLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("TownLevel");
	//GameEngineCore::ChangeLevel("PlayLevel");

	//// ȸ�������� �������� �˾Ƴ��� ���
	//float4 PlayerPos = {3, 5};
	//float4 MonsterPos = {5, 5};

	//float4 PlayerDir = { 0, 1, 0 };
	//float4 PlayerLook = (PlayerPos - MonsterPos).NormalizeReturn();


	//float4 Check = float4::Cross3D(PlayerDir, PlayerLook);

	//// float4 Rev = float4::Cross3D({0, 10, 0}, { 0.01f, -10.0f, 0 });

	//if (0 > Check.Z)
	//{
	//	// �������� ���ƶ�.
	//}

	//int a = 0;

}

void ContentsCore::Update(float _Delta)
{
	//HDC DC;
	//{
	//	// ������ Ŭ����
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