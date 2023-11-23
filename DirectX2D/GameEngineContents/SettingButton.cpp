#include "PreCompile.h"
#include "SettingButton.h"

SettingButton::SettingButton()
{
}

SettingButton::~SettingButton()
{
}

void SettingButton::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentsResources");
	Dir.MoveChild("ContentsResources\\Texture\\UI\\Title\\Option_KOR");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		GameEngineTexture::Load(File.GetStringPath());
	}
	GameEngineSprite::CreateSingle("OptionOff_Kor.png");
	GameEngineSprite::CreateSingle("OptionOn_Kor.png");

	ButtonRenderer = CreateComponent<GameEngineSpriteRenderer>(TitleRenderOrder::UI);
	ButtonRenderer->SetSprite("OptionOff_Kor.png");

	float4 Scale = ButtonRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	ButtonRenderer->SetImageScale(Scale);

	ButtonCollision = CreateComponent<GameEngineCollision>(CollisionType::Button);
	ButtonCollision->SetCollisionType(ColType::AABBBOX2D);
	ButtonCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	ButtonCollision->Transform.SetLocalScale(Scale);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -(HalfWindowScale.Y + 175.0f), -500.0f });
}
void SettingButton::Update(float _Delta)
{
	EventParameter ButtonEvent;
	ButtonEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ButtonRenderer->SetSprite("OptionOn_Kor.png");
			float4 Scale = ButtonRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
			ButtonRenderer->SetImageScale(Scale);
		};
	ButtonEvent.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			
		};
	ButtonEvent.Exit = [&](class GameEngineCollision* _This, class GameEngineCollision* _Ohter)
		{
			ButtonRenderer->SetSprite("OptionOff_Kor.png");
			float4 Scale = ButtonRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
			ButtonRenderer->SetImageScale(Scale);
		};
	ButtonCollision->CollisionEvent(CollisionType::Mouse, ButtonEvent);
}