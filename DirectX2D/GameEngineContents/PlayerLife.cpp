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
	LifeBar->SetImageScale({ 196.0f, 40.0f });
	LifeBar->SetPivotType(PivotType::Left);

	//LifeWave = CreateComponent<GameEngineUIRenderer>(RenderOrder::FrontUI);
	//LifeWave->CreateAnimation("LifeWave", "LifeWave");
	//LifeWave->ChangeAnimation("LifeWave");
	//float4 LifeWaveScale = LifeWave->GetCurSprite().Texture->GetScale() * 4.0f;
	//LifeWave->SetImageScale(LifeWaveScale);
	//LifeWave->SetPivotType(PivotType::Left);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ -(HalfWindowScale.X - (Scale.X / 2.0f) - 16.0f), HalfWindowScale.Y - (Scale.Y / 2.0f) - 16.0f });
	LifeBar->Transform.SetLocalPosition({ -60.0f, 0.0f });
	//LifeWave->Transform.SetLocalPosition(LifeBar->Transform.GetLocalPosition().X + LifeBar->GetImageTransform().GetLocalScale().X);

	LevelText = CreateComponent<GameEngineUIRenderer>(RenderOrder::Text);
	LevelText->SetText("Perfect DOS VGA 437", "30", 40.0f, float4::WHITE, FW1_CENTER);
	LevelText->Transform.SetLocalPosition({ -100.0f, 18.0f });

	LifeText = CreateComponent<GameEngineUIRenderer>(RenderOrder::Text);
	LifeText->SetText("Perfect DOS VGA 437", PlayerCurHp + " / " + PlayerMaxHp, 40.0f, float4::WHITE, FW1_CENTER);
	LifeText->Transform.SetLocalPosition({ 41.0f, 18.0f });
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

	PlayerCurHp = std::to_string(Player::GetMainPlayer()->GetCurHp());
	PlayerMaxHp = std::to_string(Player::GetMainPlayer()->GetMaxHp());
	LifeText->SetText("Perfect DOS VGA 437", PlayerCurHp + " / " + PlayerMaxHp, 40.0f, float4::WHITE, FW1_CENTER);
	SetLifeBarScale();
}

void PlayerLife::SetLifeBarScale()
{
	float Per = Player::GetMainPlayer()->GetCurHp() / Player::GetMainPlayer()->GetMaxHp() * 100.0f;
	float LifeBarScale = MaxLifeBarScaleX / 100.0f * Per;

	LifeBar->SetImageScale({ LifeBarScale, 40.0f });
}