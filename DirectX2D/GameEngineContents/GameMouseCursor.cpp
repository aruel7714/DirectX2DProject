#include "PreCompile.h"
#include "GameMouseCursor.h"

GameMouseCursor::GameMouseCursor()
{
}

GameMouseCursor::~GameMouseCursor()
{
}

void GameMouseCursor::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentsResources");
	Dir.MoveChild("ContentsResources\\Texture\\UI\\MouseCursor");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		GameEngineTexture::Load(File.GetStringPath());
	}
	GameEngineSprite::CreateSingle("ShootingCursor2.png");

	GameEngineCore::MainWindow.CursorOff();

	MouseRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mouse);
	MouseRenderer->SetSprite("ShootingCursor2.png");

	float4 Scale = MouseRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	MouseRenderer->SetImageScale(Scale);
}
void GameMouseCursor::Update(float _Delta)
{
	float4 MousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	Transform.SetLocalPosition(MousePos);
}