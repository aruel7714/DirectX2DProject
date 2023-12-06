#include "PreCompile.h"
#include "PlayerFood.h"

PlayerFood::PlayerFood()
{
}

PlayerFood::~PlayerFood()
{
}

void PlayerFood::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\UI\\PlayerFood");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("PlayerFood.png");

	FoodRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::BackUI);
	FoodRenderer->SetSprite("PlayerFood.png");
	float4 FoodScale = FoodRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	FoodRenderer->SetImageScale(FoodScale);

	FoodText = CreateComponent<GameEngineUIRenderer>(RenderOrder::BackUI);
	FoodText->SetText("Perfect DOS VGA 437", "0", 30.0f, float4::WHITE, FW1_LEFT);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ -HalfWindowScale.X + 32.0f, -HalfWindowScale.Y + 32.0f });
	FoodText->Transform.SetLocalPosition({ 40.0f, 16.0f });
}
void PlayerFood::Update(float _Delta)
{

}