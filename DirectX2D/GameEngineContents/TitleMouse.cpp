#include "PreCompile.h"
#include "TitleMouse.h"

TitleMouse::TitleMouse()
{
}

TitleMouse::~TitleMouse()
{
}

void TitleMouse::Start()
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
	GameEngineSprite::CreateSingle("BasicCursor.png");

	GameEngineCore::MainWindow.CursorOff();

	MouseRenderer = CreateComponent<GameEngineSpriteRenderer>(TitleRenderOrder::Mouse);
	MouseRenderer->SetSprite("BasicCursor.png");

	float4 Scale = MouseRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	MouseRenderer->SetImageScale(Scale);

	MouseCollision = CreateComponent<GameEngineCollision>(CollisionType::Mouse);
	MouseCollision->SetCollisionType(ColType::SPHERE2D);
	MouseCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	MouseCollision->Transform.SetLocalScale({ 4.0f, 4.0f, 1.0f });
}
void TitleMouse::Update(float _Delta)
{
	float4 MousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	Transform.SetLocalPosition(MousePos);
}