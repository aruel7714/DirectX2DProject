#include "PreCompile.h"
#include "PlayerLife.h"

PlayerLife::PlayerLife()
{
}

PlayerLife::~PlayerLife()
{
}

void PlayerLife::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\UI\\PlayerLife");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("PlayerLifeBase1.png");
	GameEngineSprite::CreateSingle("PlayerLifeBack.png");

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\UI\\LifeBar");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("LifeBar.png");

	//if (nullptr == GameEngineSprite::Find("LifeWave"))
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("ContentsResources");
	//	Dir.MoveChild("ContentsResources\\Texture\\UI\\");

	//	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	//	for (size_t i = 0; i < Directorys.size(); i++)
	//	{
	//		GameEngineDirectory& Dir = Directorys[i];

	//		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	//	}
	//}

	LifeBack = CreateComponent<GameEngineUIRenderer>(RenderOrder::BackUI);
	LifeBack->SetSprite("PlayerLifeBack.png");
	float4 Scale = LifeBack->GetCurSprite().Texture->GetScale() * 4.0f;
	LifeBack->SetImageScale(Scale);

	LifeBase = CreateComponent<GameEngineUIRenderer>(RenderOrder::FrontUI);
	LifeBase->SetSprite("PlayerLifeBase1.png");
	LifeBase->SetImageScale(Scale);

	LifeBar = CreateComponent<GameEngineUIRenderer>(RenderOrder::MiddleUI);
	LifeBar->SetSprite("LifeBar.png");
	LifeBar->SetImageScale({ 188.0f, 40.0f });
	LifeBar->SetPivotType(PivotType::Left);

	//LifeWave = CreateComponent<GameEngineUIRenderer>(RenderOrder::FrontUI);
	//LifeWave->CreateAnimation("LifeWave", "LifeWave");
	//LifeWave->ChangeAnimation("LifeWave");
	//float4 LifeWaveScale = LifeWave->GetCurSprite().Texture->GetScale() * 4.0f;
	//LifeWave->SetImageScale(LifeWaveScale);
	//LifeWave->SetPivotType(PivotType::Left);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ -(HalfWindowScale.X - (Scale.X / 2.0f) - 16.0f), HalfWindowScale.Y - (Scale.Y / 2.0f) - 16.0f });
	LifeBar->Transform.SetLocalPosition({ -56.0f, 0.0f });
	//LifeWave->Transform.SetLocalPosition(LifeBar->Transform.GetLocalPosition().X + LifeBar->GetImageTransform().GetLocalScale().X);
}
void PlayerLife::Update(float _Delta)
{
	float4 LocalPosition = Transform.GetLocalPosition();
	float4 WorldPosition = Transform.GetWorldPosition();
	/*float4 BackLocalScale = LifeBack->GetImageTransform().GetLocalScale();
	float4 BackWorldScale = LifeBack->GetImageTransform().GetWorldScale();
	float4 BaseLocalScale = LifeBase->GetImageTransform().GetLocalScale();
	float4 BaseWorldScale = LifeBase->GetImageTransform().GetWorldScale();*/
	int a = 0;
}