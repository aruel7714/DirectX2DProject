#include "PreCompile.h"
#include "PlayerGold.h"

PlayerGold::PlayerGold()
{
}

PlayerGold::~PlayerGold()
{
}

void PlayerGold::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\UI\\PlayerGold");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("PlayerGold.png");

	GoldRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::BackUI);
	GoldRenderer->SetSprite("PlayerGold.png");
	float4 GoldScale = GoldRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	GoldRenderer->SetImageScale(GoldScale);

	GoldText = CreateComponent<GameEngineUIRenderer>(RenderOrder::BackUI);
	GoldText->SetText("µ¸¿ò", "30", 40.0f, float4::WHITE, FW1_LEFT);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ -HalfWindowScale.X + 32.0f, -HalfWindowScale.Y + 64.0f });
	GoldText->Transform.SetLocalPosition({ 32.0f, 0.0f });
}
void PlayerGold::Update(float _Delta)
{

}