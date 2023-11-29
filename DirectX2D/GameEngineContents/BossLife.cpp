#include "PreCompile.h"
#include "BossLife.h"

BossLife::BossLife()
{
}

BossLife::~BossLife()
{
}

void BossLife::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\UI\\BossLife");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("BossLifeBack.png");
	GameEngineSprite::CreateSingle("BossLifeBase.png");
	GameEngineSprite::CreateSingle("BossSkellPortrait.png");

	BossLifeBack = CreateComponent<GameEngineUIRenderer>(RenderOrder::BackUI);
	BossLifeBack->SetSprite("BossLifeBack.png");
	float4 Scale = BossLifeBack->GetCurSprite().Texture->GetScale() * 4.0f;
	BossLifeBack->SetImageScale(Scale);

	BossLifeBase = CreateComponent<GameEngineUIRenderer>(RenderOrder::FrontUI);
	BossLifeBase->SetSprite("BossLifeBase.png");
	BossLifeBase->SetImageScale(Scale);

	BossLifeBar = CreateComponent<GameEngineUIRenderer>(RenderOrder::MiddleUI);
	BossLifeBar->SetSprite("LifeBar.png");
	BossLifeBar->SetPivotType(PivotType::Left);
	BossLifeBar->SetImageScale({ 400.0f, 40.0f });

	BossImage = CreateComponent<GameEngineUIRenderer>(RenderOrder::FrontUI);
	BossImage->SetSprite("BossSkellPortrait.png");
	float4 ImageScale = BossImage->GetCurSprite().Texture->GetScale() * 4.0f;
	BossImage->SetImageScale(ImageScale);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 0.0f, -HalfWindowScale.Y + Scale.Y + 16.0f});
	BossLifeBar->Transform.SetLocalPosition({ -164.0f, 0.0f });
	BossImage->Transform.SetLocalPosition({ -206.0f, 0.0f });

}
void BossLife::Update(float _Delta)
{

}

void BossLife::SetLifeBarScale(float _Per)
{
	float LifeBarScale = MaxLifeBarScaleX / 100.0f * _Per;

	if (0 >= _Per)
	{
		BossLifeBar->SetImageScale({ 0.0f, 40.0f });
	}
	else
	{
		BossLifeBar->SetImageScale({ LifeBarScale, 40.0f });
	}

	//BossLifeBar->SetImageScale({ LifeBarScale, 40.0f });
}