#include "PreCompile.h"
#include "GameExitButton.h"

GameExitButton::GameExitButton()
{
}

GameExitButton::~GameExitButton()
{
}

void GameExitButton::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentsResources");
	Dir.MoveChild("ContentsResources\\Texture\\UI\\Title\\Exit_KOR");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		GameEngineTexture::Load(File.GetStringPath());
	}
	GameEngineSprite::CreateSingle("ExitOff_Kor.png");
	GameEngineSprite::CreateSingle("ExitOn_Kor.png");

	ButtonRenderer = CreateComponent<GameEngineSpriteRenderer>(TitleRenderOrder::UI);
	ButtonRenderer->SetSprite("ExitOff_Kor.png");

	float4 Scale = ButtonRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	ButtonRenderer->SetImageScale(Scale);

	ButtonCollision = CreateComponent<GameEngineCollision>(CollisionType::Button);
	ButtonCollision->SetCollisionType(ColType::AABBBOX2D);
	ButtonCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	ButtonCollision->Transform.SetLocalScale(Scale);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -(HalfWindowScale.Y + 230.0f), -500.0f });
}
void GameExitButton::Update(float _Delta)
{
	EventParameter ButtonEvent;
	ButtonEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ButtonRenderer->SetSprite("ExitOn_Kor.png");
			float4 Scale = ButtonRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
			ButtonRenderer->SetImageScale(Scale);
		};
	ButtonEvent.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{

		};
	ButtonEvent.Exit = [&](class GameEngineCollision* _This, class GameEngineCollision* _Ohter)
		{
			ButtonRenderer->SetSprite("ExitOff_Kor.png");
			float4 Scale = ButtonRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
			ButtonRenderer->SetImageScale(Scale);
		};
	ButtonCollision->CollisionEvent(CollisionType::Mouse, ButtonEvent);
}