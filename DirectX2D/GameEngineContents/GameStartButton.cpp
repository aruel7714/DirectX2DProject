#include "PreCompile.h"
#include "GameStartButton.h"

GameStartButton::GameStartButton()
{
}

GameStartButton::~GameStartButton()
{
}

void GameStartButton::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentsResources");
	Dir.MoveChild("ContentsResources\\Texture\\UI\\Title\\Play_KOR");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		GameEngineTexture::Load(File.GetStringPath());
	}
	GameEngineSprite::CreateSingle("PlayOff_Kor.png");
	GameEngineSprite::CreateSingle("PlayOn_Kor.png");

	ButtonRenderer = CreateComponent<GameEngineSpriteRenderer>(TitleRenderOrder::UI);
	ButtonRenderer->SetSprite("PlayOff_kor.png");
	
	float4 Scale = ButtonRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	ButtonRenderer->SetImageScale(Scale);

	ButtonCollision = CreateComponent<GameEngineCollision>(CollisionType::Button);
	ButtonCollision->SetCollisionType(ColType::AABBBOX2D);
	ButtonCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	ButtonCollision->Transform.SetLocalScale(Scale);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -(HalfWindowScale.Y + 120.0f), -500.0f });

	GameEngineInput::AddInputObject(this);

	Fade = GetLevel()->CreateActor<LevelFadeIn>(RenderOrder::Fade);
	Fade->Off();
}
void GameStartButton::Update(float _Delta)
{
	EventParameter ButtonEvent;
	ButtonEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ButtonRenderer->SetSprite("PlayOn_kor.png");
			float4 Scale = ButtonRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
			ButtonRenderer->SetImageScale(Scale);
		};
	ButtonEvent.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			if (GameEngineInput::IsPress(VK_LBUTTON, this))
			{
				Fade->On();
				
			}
		};
	ButtonEvent.Exit = [&](class GameEngineCollision* _This, class GameEngineCollision* _Ohter)
		{
			ButtonRenderer->SetSprite("PlayOff_kor.png");
			float4 Scale = ButtonRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
			ButtonRenderer->SetImageScale(Scale);
		};
	ButtonCollision->CollisionEvent(CollisionType::Mouse, ButtonEvent);

	if (true == Fade->IsUpdate())
	{
		if (1.0f <= Fade->GetMulColorA())
		{
			GameEngineCore::ChangeLevel("TownLevel");
		}
	}
}